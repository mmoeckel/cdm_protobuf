#!/usr/bin/env python
# -*- coding: utf-8 -*-

# This script takes a Protobuf definition file (.proto) and generates two C++
# header files: One containing structs and enums representing the data that is
# held by the protocol buffer, and one containing adapter functions to translate
# between that file and the one generated by protoc.
# This provides you with a data structure that can be used independently from the
# protobuf library but contains the same data and can easily be translated to and
# from a protocol buffer.
# This is a very early revision of the script that only covers a small subset of
# the proto file definition. Feel free to extend it to suit your needs and/or provide
# feedback (my GitHub user name is mmoeckel).
# Usage: python3 proto2h.py <input.proto> <output_header.h> <output_adapter.h>

import sys
import os
import re

stringRequired = 0
vectorRequired = 0

# Source proto file name (i.e. cdm.proto)
protoFileName = sys.argv[1]
# Name of the generated header file (i.e. cdm.cpp.h)
outputHeaderName = sys.argv[2]
# File name for the generated adapter class
adapterFileName = sys.argv[3]

# Fill in default values based on (protobuf) data type
def getDefaultValue(type):
    if (type == "double"):
        return " = 0.0"
    elif (type == "uint32"):
        return " = 0"
    elif (type == "string"):
        return " = \"\""
    else:
        return ""

# Converts a protobuf enum to a C++ enum
# Input is a string containing the protobuf enum ("enum <name> { ... }")
# Output is the corresponding C++ enum
def convertEnum(e):
    name = re.search(r"enum\s+(\w+)\s*{",e).group(1)
    elements = re.findall(r"\s*(\w+)\s*=\s*(\d+);",e)

    cppEnum = "enum " + name + "\n{\n"
    for v in elements[:-1]:
        cppEnum += "    " + v[0] + " = " + v[1] + ",\n"
    # Last element has no trailing comma
    cppEnum += "    " + elements[-1][0] + " = " + elements[-1][1] + "\n};\n\n"

    return cppEnum

# Generate adapter functions to convert between the protobuf enum and the generated C++ enum
def generateEnumAdapter(e,package,namespace):
    name = re.search(r"enum\s+(\w+)\s*{",e).group(1)
    elements = re.findall(r"\s*(\w+)\s*=\s*(\d+);",e)

    adapterFunctions = ""
    p2c = "static inline " + namespace + "::" + name + " " + name + "(const " + package   + "::" + name + " in)\n{\n"
    c2p = "static inline " + package   + "::" + name + " " + name + "(const " + namespace + "::" + name + " in)\n{\n"
    for v in elements:
        p2c += "    if (in == " + package   + "::" + v[0] + ") return " + namespace + "::" + v[0] + ";\n"
        c2p += "    if (in == " + namespace + "::" + v[0] + ") return " + package   + "::" + v[0] + ";\n"
    p2c += "    return "+namespace+"::"+elements[0][0]+";\n}\n\n"
    c2p += "    return "+package+"::"+elements[0][0]+";\n}\n\n"

    adapterFunctions += p2c
    adapterFunctions += c2p

    return adapterFunctions


# Converts a protobuf message to a C++ struct
# Input is a string containing the protobuf message ("message <name> { ... }")
# Output is the corresponding C++ struct
def convertMessage(m):
    name = re.search(r"message\s+(\w+)\s*{",m).group(1)
    elements = re.findall(r"\s*(repeated )*\s*([\w.]+)\s+(\w+)\s*=\s*(\d+);",m)

    cppStruct = "struct " + name + "\n{\n"
    for v in elements:
        repeat = v[0]
        type = v[1]
        type = re.sub("\.","_C::",type)
        variable = v[2]
        if (type == "string"):
            global stringRequired
            stringRequired = 1
        if (repeat == "repeated "):
            global vectorRequired
            vectorRequired = 1
            cppStruct += "    std::vector<" + type + "> " + variable + ";\n"
        else:
            defaultValue = getDefaultValue(type)
            cppStruct += "    " + type + " " + variable + defaultValue + ";\n"
    cppStruct += "};\n\n"
    # Replace some protobuf data type names with their C++ counterparts.
    # This list needs to be extended.
    cppStruct = re.sub("string","std::string",cppStruct)
    cppStruct = re.sub("uint32","unsigned int",cppStruct)
    return cppStruct


# Generate adapter functions to convert between the protobuf message and the generated C++ struct
def generateMessageAdapter(m,package,namespace,enumNames,messageNames):
    name = re.search(r"message\s+(\w+)\s*{",m).group(1)
    elements = re.findall(r"\s*(repeated )*\s*([\w.]+)\s+(\w+)\s*=\s*(\d+);",m)

    adapterFunctions = ""
    p2c = "static inline " + namespace + "::" + name + " " + name + "(const " + package   + "::" + name + " in)\n{\n"
    c2p = "static inline " + package   + "::" + name + " " + name + "(const " + namespace + "::" + name + " in)\n{\n"
    p2c += "    " + namespace + "::" + name + " result;\n"
    c2p += "    " + package   + "::" + name + " result;\n"
    for v in elements:
        otherPackage = ""
        repeat = v[0]
        type = v[1]
        if ("." in type):
            otherPackage = type.split(".")[0]
            type = type.split(".")[1]
            # FIXME: This is assuming that everything from another package is a message!
            messageNames.append(type)
        variable = v[2]
        if type in enumNames:
            # Element is an enum. Convert between protobuf and C++ before assigning.
            p2c += "    result." + variable + " = " + type + "(in." + variable.lower() + "());\n"
            c2p += "    result.set_" + variable.lower() + "(" + type + "(in." + variable + "));\n";
        elif type in messageNames:
            if (repeat == "repeated "):
                p2c_in = type + "(in." + variable.lower() + "(i))"
                if (otherPackage != ""):
                    p2c_in = otherPackage + "_PA::" + p2c_in
                p2c += "    for (int i=0; i<in." + variable.lower() + "_size(); i++) { result." + variable + ".push_back(" + p2c_in + "); }\n"
                c2p_in = type + "(in." + variable + "[i]))"
                if (otherPackage != ""):
                    c2p_in = otherPackage + "_PA::" + c2p_in
                    c2p += "    for (int i=0; i<in." + variable + ".size(); i++) {\n"
                    c2p += "        result.mutable_" + variable.lower() + "()->AddAllocated(new " + otherPackage + "::" + type + "(" + c2p_in + ");\n"
                    c2p += "    }\n"
                else:
                    c2p += "    for (int i=0; i<in." + variable + ".size(); i++) {\n"
                    c2p += "        result.mutable_" + variable.lower() + "()->AddAllocated(new " + package + "::" + type + "(" + c2p_in + ");\n"
                    c2p += "    }\n"

            else:
                # Element is a message/struct. Convert and use pointers and "set_allocated_" functions.
                p2c += "    result." + variable + " = " + type + "(in." + variable.lower() + "());\n"
                c2p += "    " + package + "::" + type + "* " + variable.lower() + "_inst = new " + package + "::" + type + "(" + type + "(in." + variable + "));\n"
                c2p += "    result.set_allocated_" + variable.lower() + "(" + variable.lower() + "_inst);\n"
        else:
            # Element is a primitive data type
            if (repeat == "repeated "):
                p2c_in = "in." + variable.lower() + "(i)"
                p2c += "    for (int i=0; i<in." + variable.lower() + "_size(); i++) { result." + variable + ".push_back(" + p2c_in + "); }\n"
                c2p += "    for (int i=0; i<in." + variable + ".size(); i++) { result.add_" + variable.lower() + "(in." + variable + "[i]); }\n"
            else:
                p2c_in = "in." + variable.lower() + "()"
                p2c += "    result." + variable + " = " + p2c_in + ";\n"
                c2p += "    result.set_" + variable.lower() + "(in." + variable + ");\n"
    p2c += "    return result;\n}\n\n"
    c2p += "    return result;\n}\n\n"

    adapterFunctions += p2c
    adapterFunctions += c2p

    return adapterFunctions


with open(protoFileName,"r") as protoFile:

    # Read in proto file
    proto = protoFile.read()
    # Remove // comments
    proto = re.sub(r"\s*//.*[\r\n]","\n",proto)
    # Remove (single-line) /**/ comments
    proto = re.sub(r"\s*/\*.*\*/","",proto)
    # Remove new lines
    proto = re.sub(r"[\r\n]"," ",proto)
    # Remove extra white spaces
    proto = re.sub(r"\s+"," ",proto)

    # Find the package name
    package = re.search(r"package\s+(\w+);",proto).group(1)
    # Add "_C" to the package name to form the generated C++ namespace
    namespace = package + "_C"

    # Get list of enum definitions
    enums = re.findall(r"enum\s+\w+[\r\n\s]*\{[\w\s\d=;]*\}",proto)
    # Get list of enum names
    enumNames = re.findall(r"enum\s+(\w+)[\r\n\s]*\{",proto)
    # Get list of message definitions
    messages = re.findall(r"message\s+\w+[\r\n\s]*\{[\w\s\d.=;]*\}",proto)
    # Get list of message names
    messageNames = re.findall(r"message\s+(\w+)[\r\n\s]*\{",proto)

    # Empty strings to hold generated enums, structs and adapter functions
    cppEnums = ""
    cppStructs = ""
    adapterFunctions = ""

    # convert all protobuf enums and generate adapter functions
    for e in enums:
        cppEnums += convertEnum(e)
        adapterFunctions += generateEnumAdapter(e,package,namespace)

    # convert all protobuf messages and generate adapter functions
    for m in messages:
        cppStructs += convertMessage(m)
        adapterFunctions += generateMessageAdapter(m,package,namespace,enumNames,messageNames)

    # Find imported proto files
    imports = re.findall(r"\s*import(\s+public)*\s+\"(\w+)\.proto\"",proto)

    # Generate and write header file
    headerFile = "//Generated by proto2h.py, do not modify!\n"
    headerFile += "#ifndef " + namespace.upper() + "_H_\n"
    headerFile += "#define " + namespace.upper() + "_H_\n\n"
    for i in imports:
        headerFile += "#include \"" + i[1] + ".cpp.h\"\n"
    if (stringRequired > 0):
        headerFile += "#include <string>\n"
    if (vectorRequired > 0):
        headerFile += "#include <vector>\n"
    headerFile += "\nnamespace " + namespace + " {\n\n"
    headerFile += cppEnums
    headerFile += cppStructs
    headerFile += "}\n"
    headerFile += "#endif\n"

    f = open(outputHeaderName,"w")
    f.write(headerFile)
    f.close()

    # Generate and write adapter file
    adapterFile = "//Generated by proto2h.py, do not modify!\n"
    adapterFile += "#ifndef " + package.upper() + "_PROTOBUF_ADAPTER_H_\n"
    adapterFile += "#define " + package.upper() + "_PROTOBUF_ADAPTER_H_\n\n"
    for i in imports:
        adapterFile += "#include \"" + i[1] + ".pb.h\"\n"
        adapterFile += "#include \"" + i[1] + ".cpp.h\"\n"
        adapterFile += "#include \"" + i[1] + "_protobuf_adapter.h\"\n"
    adapterFile += "#include \"" + os.path.splitext(os.path.basename(protoFileName))[0] + ".pb.h\"\n";
    adapterFile += "#include \"" + os.path.basename(outputHeaderName) + "\"\n\n";
    adapterFile += "class " + package + "_PA\n{\npublic:\n"
    adapterFile += adapterFunctions
    adapterFile += "\n};\n\n#endif\n"

    f = open(adapterFileName,"w")
    f.write(adapterFile)
    f.close()

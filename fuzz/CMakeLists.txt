cmake_minimum_required(VERSION 3.10)

project(CJsonObjectLib LANGUAGES CXX)

include_directories(../)

add_library(cjsonobject STATIC ../CJsonObject.cpp ../cJSON.c)

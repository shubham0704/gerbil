#!/bin/bash
protoc --grpc_out=./ --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./gerbil.proto
protoc --cpp_out=. ./gerbil.proto 
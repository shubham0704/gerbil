vole_module_name(gerbil_service)
vole_module_description("Gerbil GRPC Service to access all modules in any language")
vole_module_variable(Gerbil_GRPC_Service)

# vole_add_required_dependencies(OPENCV)
# vole_add_required_modules(imginput)

vole_add_required_dependencies(GRPC)
get_filename_component(hw_proto "./gerbil.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

# custom command can falter because if its discovered as global cmake then relative paths wont work
# I need these header and cc files in this directory only
set(hw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/gerbil.pb.cc")
set(hw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/gerbil.pb.h")
set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/gerbil.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/gerbil.grpc.pb.h")
add_custom_command(
      OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
      COMMAND protoc
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${hw_proto_path}"
        --plugin=protoc-gen-grpc="/usr/local/bin/grpc_cpp_plugin"
        "${hw_proto}"
      DEPENDS "${hw_proto}")
# do protoc stuff
vole_compile_library(
	gerbil.pb.cc
	gerbil.grpc.pb.cc
	gerbil_server
)# add flags related to grpc and protobuf during compilation or check if the flags for the dependencies we have included are automatically passed while compilation

vole_add_executable("gerbil_service" "gerbil_server")
vole_add_module()

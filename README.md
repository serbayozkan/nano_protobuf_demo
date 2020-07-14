nano_protobuf_demo

Demo software on Eclipse IDE to send sensor and payload data from client device to server device.

links:
- https://github.com/nanopb/nanopb

Compiling proto file for Windows:
- Download the Windows Protofiles from https://jpa.kapsi.fi/nanopb/download/
- Open the command line on \nanopb-0.4.2-windows-x86\generator-bin
- protoc --nanopb_out=. filename.proto
- If protoc is not found, make sure that python is installed

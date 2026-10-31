**Jhm2 WebSocket Server**

Converts WebSocket requests from a client into Jhm2ParamMsgRequests for use by the AisJhm2DataServer. Currently supports ParameterRequest(2), FileRequest, and CommandRequest(2). Parameter and File requests can be one-time or periodic.

The AIS application will create an instance of the Jhm2WsServer, providing a reference to itself, the endPoint string, and port when starting the server. See the [header](Jhm2WsServer.h) for interface details.

Client should send messages that adhere to the [Jhm2WsServerRequest JSON Schema](jhm2WsServerRequest.schema.json). The responses will adhere to the [Jhm2WsServerResponse JSON Schema](jhm2WsServerResponse.schema.json)

An HTML test client can be found [here](jhm2WsClientTest.html).

This application used [Simple WebSocketServer](../Simple-WebSocket-Server/README.md).
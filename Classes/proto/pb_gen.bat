@echo off
SsuPBCpp PacketsCtoS.proto ../Packet/PacketsCtoS.cpp ../Packet/PacketsCtoS.h
SsuPBCpp PacketsStoC.proto ../Packet/PacketsStoC.cpp ../Packet/PacketsStoC.h
protoa PacketsCtoS.proto ../Packet/Builder.inl CS PacketsStoC.proto ../Packet/Handler/ SC


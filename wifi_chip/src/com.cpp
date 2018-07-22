#include "com.hpp"

void ComClass::onReceived(ComMessage * req) 
{
    switch(req->getCommand())
    {
        case ComClass::CMD_DEBUG:
        {
            Debug::print("Remote: ");
            Debug::print(req->getValue().c_str());
            transmit(req->getCommand(), req->getKey(), "OK");
            break;
        }
        case ComClass::CMD_READ:
        {
            if(req->getKey() == ComClass::KEY_IO)
            {
                File io = Settings.getIOSettings();
                transmit(req->getCommand(), req->getKey(), io);
                io.close();
            }
            else if(req->getKey() == ComClass::KEY_PROGRAM)
            {
                if(req->getValue() == NULL)
                {
                    String programs = String(Settings.getPrograms());
                    transmit(req->getCommand(), req->getKey(),  programs.c_str());
                }
                else {
                    String index = req->getValue();
                    File prog = Settings.getProgram(index);
                    transmit(req->getCommand(), req->getKey(),  prog);
                    prog.close();
                }
            }
            break;
        }
        case ComClass::CMD_WRITE:
        {
            /*
            if(req->getKey() == KEY_START_PROG)
            {
                String index = req->getValue();
                File prog = Settings.getProgram(index);
                StaticJsonBuffer<512> jsonBuffer;
                JsonObject &root = jsonBuffer.parseObject(prog);
                root["active"] = 1;
                String newProg;
                root.printTo(newProg);
                prog.close();
                Settings.setProgram(index, newProg);
            }
            else if(req->getKey() == KEY_STOP_PROG)
            {
                String index = req->getValue();
                File prog = Settings.getProgram(index);
                StaticJsonBuffer<512> jsonBuffer;
                JsonObject &root = jsonBuffer.parseObject(prog);
                root["active"] = 0;
                String newProg;
                root.printTo(newProg);
                prog.close();
                Settings.setProgram(index, newProg);
            }
          */
            transmit(req->getCommand(), req->getKey(), "OK");
            break;
        }
    }
   // delete req;
}

ComClass COM;
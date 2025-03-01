#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MSG_SIZE 100
#define QUEUE_KEY 1234

struct message {
  long msg_type;
  char msg_text[MSG_SIZE];
};

int main() {
  int msgid = msgget(QUEUE_KEY, 0666 | IPC_CREAT);
  if (msgid == -1) {
    perror("msgget");
    return 1;
  }

  message msg;
  while (true) {
    if (msgrcv(msgid, &msg, sizeof(msg) - sizeof(long), 1, 0) == -1) {
      perror("msgrcv");
      exit(1);
    }
    std::cout << "You: " << msg.msg_text << std::endl;

    if (strcmp(msg.msg_text, "exit") == 0)
      break;

    msg.msg_type = 2;
    std::string reply = std::string("Received: ") + msg.msg_text;
    strncpy(msg.msg_text, reply.c_str(), MSG_SIZE);

    if (msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 0) == -1) {
      perror("msgsnd");
      exit(1);
    }
    if (strcmp(msg.msg_text, "exit") == 0)
      break;
  }

  msgctl(msgid, IPC_RMID, NULL); // Cleanup message queue after receiving "exit"
  return 0;
}

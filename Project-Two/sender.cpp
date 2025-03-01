
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
  // Get message queue
  int msgid = msgget(QUEUE_KEY, 0666 | IPC_CREAT);
  if (msgid == -1) {
    perror("msgget");
    return 1;
  }

  message msg;
  while (true) {
    std::cout << "You: ";
    std::cin.getline(msg.msg_text, MSG_SIZE);
    msg.msg_type = 1; // Message type 1 (Sender to Receiver)

    // Send message to receiver
    if (msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 0) == -1) {
      perror("msgsnd");
      exit(1);
    }

    if (strcmp(msg.msg_text, "exit") == 0)
      break;

    // Receive response from receiver (msg_type = 2)
    if (msgrcv(msgid, &msg, sizeof(msg) - sizeof(long), 2, 0) == -1) {
      perror("msgrcv");
      exit(1);
    }

    std::cout << "A: " << msg.msg_text << std::endl;
  }

  return 0;
}

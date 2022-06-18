# socket Example

Overview
--------
An example of the socket concept written in C++, the program can perform as a server and as a client.
Both sides have to run in the same machine in order for the connection to be successful.
The program does not validates arguments.
port should be an integer between 1025 to 9999.
terminal_command_to_run_in_server should be a system command under quotes.

Usage
-----
* Create executable:

    ```make```

* Server Usage:

    ```./socket server <port>```

* Client Usage:

    ```./socket client <port> <terminal_command_to_run_in_server>```

Credits
-------
This project was made as part of my Computer Science studies in the Hebrew University.
It was given as an exercise in course 67808 ( Operating Systems ) which I took in 2022.

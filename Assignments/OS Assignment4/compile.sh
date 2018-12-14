javac *.java &&
jar -cmf FileTransferServer.mf FileTransferServer.jar FileTransferServer.class &&
jar -cmf FileTransferClient.mf FileTransferClient.jar FileTransferClient.class &&
gcc -o init init.c

#begin transferring
./init
LIBS =  -lcurl -lssl -lcrypto -lz -lwldap32 -lws2_32 -lwinmm -lgdi32
INCLUDE_DIR = -I./dependencies/include 
LIB_DIR = -L./dependencies/lib
LOCAL_INCLUDE_DIR = -I./include


all: main.o getMessages.o create.o login.o ping.o inputParse.o sendMessage.o
	mingw32-g++.exe -Wall -std=c++14 -DCURL_STATICLIB ./obj/main.o ./obj/getToken.o ./obj/sendMessage.o ./obj/create.o ./obj/getMessages.o ./obj/login.o ./obj/ping.o ./obj/inputParse.o -o ./bin/ppc.exe $(LIB_DIR) $(LIBS)
main.o:
	mingw32-g++.exe -c -Wall -std=c++14 -DCURL_STATICLIB main.cpp -o ./obj/main.o $(INCLUDE_DIR) $(LOCAL_INCLUDE_DIR)
inputParse.o:
	mingw32-g++.exe -c -Wall -std=c++14 -DCURL_STATICLIB ./src/inputParse.cpp -o ./obj/inputParse.o $(INCLUDE_DIR) $(LOCAL_INCLUDE_DIR)
getMessages.o: getToken.o
	mingw32-g++.exe -c -Wall -std=c++14 -DCURL_STATICLIB ./src/getMessages.cpp -o ./obj/getMessages.o $(INCLUDE_DIR) $(LOCAL_INCLUDE_DIR)
login.o:
	mingw32-g++.exe -c -Wall -std=c++14 -DCURL_STATICLIB ./src/login.cpp -o ./obj/login.o $(INCLUDE_DIR) $(LOCAL_INCLUDE_DIR)
create.o:
	mingw32-g++.exe -c -Wall -std=c++14 -DCURL_STATICLIB ./src/create.cpp -o ./obj/create.o $(INCLUDE_DIR) $(LOCAL_INCLUDE_DIR)
ping.o:
	mingw32-g++.exe -c -Wall -std=c++14 -DCURL_STATICLIB ./src/ping.cpp -o ./obj/ping.o $(INCLUDE_DIR) $(LOCAL_INCLUDE_DIR)
sendMessage.o:getToken.o
	mingw32-g++.exe -c -Wall -std=c++14 -DCURL_STATICLIB ./src/sendMessage.cpp -o ./obj/sendMessage.o $(INCLUDE_DIR) $(LOCAL_INCLUDE_DIR)
getToken.o:
	mingw32-g++.exe -c -Wall -std=c++14 -DCURL_STATICLIB ./util/getToken.cpp -o ./obj/getToken.o $(INCLUDE_DIR) $(LOCAL_INCLUDE_DIR)

clean:
	rm ./obj/*.o
test:
	mingw32-g++.exe -Wall -std=c++14 -DCURL_STATICLIB  ./test/tmp.cpp  -o ./bin/test.exe $(INCLUDE_DIR) $(LOCAL_INCLUDE_DIR)



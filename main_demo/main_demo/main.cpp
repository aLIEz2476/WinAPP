#include <iostream>
#include <Windows.h>
#include <process.h>
#include <string>
using namespace std;

unsigned int WINAPI InputProcess(void *arg) // arg를 통해 외부의 데이터값을 받을 수 있다.
{
	int* pData = (int*)arg;
	while (true)
	{
		scanf_s("%d", pData);
		Sleep(500);

	}
};

int main()
{
	enum WM_MSG { CREATE, COMMAND, PAINT, DESTROY, MAX };
	string strMSG[MAX] = { "CREATE", "COMMAND", "PAINT", "DESTROY" };
	HANDLE hThread = NULL;
	DWORD dwThreadID = NULL;

	
	int nMsg=CREATE;
	
	// 프로세스 : 프로그램의 가장 기본적인 처리를 담당하는 흐름 단위(메인 루프), 큰 흐름의 단위
	// 스레드 : 프로세스 내부에 처리를 하는 프름단위(반복문을 동시에 처리할 수 있다.). 큰 흐름의 하위 단위에 속하는 작은 흐름
	// 스레드는 프로그램 내부에서 처리하는 내용을 변경할 수 있어야하므로, 그 프로그램 내의 함수를 호출하여 사용한다.
	// 콜백함수 : 프로세스 내에서 호출하지 않고, 외부에서 호출하도록 하는 함수

	hThread = (HANDLE)_beginthreadex(NULL, 0, InputProcess, (void*)&nMsg, 0, (unsigned*)&dwThreadID);
	// InputProcess : 콜백함수 등록->함수의 주소 전달
	// (void*)&nMsg : 받아올 메세지의 주소를 넘김

	while (true)
	{
		
		switch (nMsg)
		{
		case CREATE:
			cout << "초기화" << endl;
			nMsg = COMMAND;
			break;
		case COMMAND:
			cout << "input command" << endl;
			for (int i = 1; i < MAX; i++)
				cout << i << ". " << " : " << strMSG[i] << endl;
			break;
		case PAINT:
			cout << "Draw on Monitor" << endl;
			break;
		case DESTROY:
			cout << "Shutdown this Program." << endl;
			exit(0);
			break;
		default:
			break;
		}
		Sleep(1000);
	}
	return 0;
}
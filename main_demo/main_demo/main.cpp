#include <iostream>
#include <Windows.h>
#include <process.h>
#include <string>
using namespace std;

unsigned int WINAPI InputProcess(void *arg) // arg�� ���� �ܺ��� �����Ͱ��� ���� �� �ִ�.
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
	
	// ���μ��� : ���α׷��� ���� �⺻���� ó���� ����ϴ� �帧 ����(���� ����), ū �帧�� ����
	// ������ : ���μ��� ���ο� ó���� �ϴ� ��������(�ݺ����� ���ÿ� ó���� �� �ִ�.). ū �帧�� ���� ������ ���ϴ� ���� �帧
	// ������� ���α׷� ���ο��� ó���ϴ� ������ ������ �� �־���ϹǷ�, �� ���α׷� ���� �Լ��� ȣ���Ͽ� ����Ѵ�.
	// �ݹ��Լ� : ���μ��� ������ ȣ������ �ʰ�, �ܺο��� ȣ���ϵ��� �ϴ� �Լ�

	hThread = (HANDLE)_beginthreadex(NULL, 0, InputProcess, (void*)&nMsg, 0, (unsigned*)&dwThreadID);
	// InputProcess : �ݹ��Լ� ���->�Լ��� �ּ� ����
	// (void*)&nMsg : �޾ƿ� �޼����� �ּҸ� �ѱ�

	while (true)
	{
		
		switch (nMsg)
		{
		case CREATE:
			cout << "�ʱ�ȭ" << endl;
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
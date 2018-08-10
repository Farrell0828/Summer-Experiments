#include <iostream>
#include <queue>
#include <vector>
#include <random>
#include <ctime>
#include <Windows.h>
using namespace std;

// ״̬ö�����Ͷ���
enum State { ready, runnig, blocked, finished };

// �����������
default_random_engine e(time(nullptr));
uniform_int_distribution<> int_1_10(1, 10);
uniform_int_distribution<> int_1_5(1, 5);
uniform_int_distribution<> int_0_2;

// PCB�ṹ�嶨��
struct PCB {
	int id;				// id
	State state;		// ״̬
	int priority;		// ���ȼ�����ֵԽ�����ȼ�Խ��
	int arrive_time;	// ����ʱ��
	int need_time;		// ��Ҫ������ʱ��
	int used_time;		// �Ѿ�����ʱ��
};

// ��ʼ��PCB
void InitPCBs(vector<PCB*>& pcbs) {
	for (int i = 0; i < pcbs.size(); i++) {
		pcbs[i] = new PCB;
		pcbs[i]->id = i + 1;
		pcbs[i]->state = ready;
		pcbs[i]->priority = int_1_5(e);
		pcbs[i]->arrive_time = int_1_10(e);
		pcbs[i]->need_time = int_1_10(e);
		pcbs[i]->used_time = 0;
	}
}

// �ͷ�PCB�ռ�
void FreePCBs(vector<PCB*>& pcbs) {
	for (auto x : pcbs) {
		delete x;
	}
}


// չʾPCB����ϸ��Ϣ
void ShowPCBInfo(const PCB* p) {
	cout << "\n����ID: " << p->id << endl
		<< "  ״̬: " << p->state << endl
		<< "  ���ȼ�: " << p->priority << endl
		<< "  ����ʱ��: " << p->arrive_time << endl
		<< "  ��Ҫ����ʱ��: " << p->need_time << endl
		<< "  �Ѿ�����ʱ��: " << p->used_time << endl;
}

// ���ݽ���״̬�����ȼ����ѵ��������ѡ��һ��Ҫ���еĽ��̣�
// ����ָ��ѡ�еĽ���PCB��ָ�룬���ѵ������Ϊ�ջ��޷�ѡ�����ؿ�ָ��nullptr
PCB* ChooseOne(const vector<PCB*>& arrived_pcbs) {
	// ���û���ѵ������
	if (arrived_pcbs.empty()) {
		return nullptr;
	}
	PCB* temp = nullptr;
	// �鿴�Ƿ��о���״̬�Ľ���
	for (auto x : arrived_pcbs) {
		// �������ʱ����Ӧ��PCB��ַ��ֵ��temp
		if (x->state == ready) {
			temp = x;
			break;
		}
	}
	// ���temp == nullptr˵��Ŀǰû�о���״̬�Ľ���
	if (temp == nullptr) {
		return nullptr;
	}
	// �����������ȼ�����Ϣѡ��Ҫ���еĽ���
	for (auto x : arrived_pcbs) {
		// ���Ǿ���״̬�Ľ���ֱ������
		if (x->state != ready) {
			continue;
		}
		// �����ǰ����x�����ȼ���choose_reault�ߣ���x��ֵ��temp
		if (x->priority > temp->priority) {
			temp = x;
		}
		// ������������ȼ���ͬ
		if (x->priority == temp->priority) {
			// ѡ�ȵ�����Ǹ�
			if (x->arrive_time < temp->arrive_time) {
				temp = x;
			}
			// �������ʱ��Ҳ��ͬ
			if (x->arrive_time == temp->arrive_time) {
				// ѡʣ�໹������ʱ��(��������ʱ��need_time��ȥ��ʹ��CPUʱ��used_time)��С���Ǹ�
				if ((x->need_time - x->used_time) <
					(temp->need_time - temp->used_time)) {
					temp = x;
				}
			}
		}
	}
	return temp;
}

int main() {
	cout << "Please input the number of N: ";
	int N;
	cin >> N;
	vector<PCB*> pcbs(N);
	InitPCBs(pcbs);
	for (auto x : pcbs) {
		ShowPCBInfo(x);
	}

	vector<PCB*> arrived_pcbs;		// ��¼�Ѿ�����Ľ���
	vector<PCB*> finished_pcbs;		// ��¼�����Ľ���
	int clock = 1;					// ʱ��ʱ��
	bool cpu_running = false;		// cup״̬
	PCB* running_pcb = nullptr;		// ָ���������еĽ��̣�Ϊ�ձ�ʾû�н�����������
	while (true) {
		// ���˿̵���Ľ�������arrived_pcbs
		cout << endl << clock << "ʱ��:\n";
		for (auto x : pcbs) {
			if (x->arrive_time == clock) {
				arrived_pcbs.push_back(x);
				cout << "  " << x->id << "�Ž��̵���\n";
			}
		}
		// �����ʱû�н���������
		if (running_pcb == nullptr) {
			// ���Դ��ѵ��������ѡ��һ����������Ϊ���н���
			running_pcb = ChooseOne(arrived_pcbs);
			if (running_pcb) {
				cout << "  " << running_pcb->id << "�Ž��̿�ʼ����\n";
			}
		}
		// �����ʱ�н���������
		if (running_pcb) {
			running_pcb->used_time++;		// ������ʱ��+1
			cout << "  " << running_pcb->id << "�Ž���������, ������"
				<< running_pcb->used_time << "��λʱ��, ��������"
				<< running_pcb->need_time << "��λʱ��" << endl;
			// ����˽������н���
			if (running_pcb->used_time == running_pcb->need_time) {
				running_pcb->state = finished;	// ���˽���״̬����Ϊ���
				finished_pcbs.push_back(running_pcb);	// ���˽�������finished_pcbs
				cout << "  " << running_pcb->id << "�Ž������н���\n";
				running_pcb = nullptr;		// ���������н���ָ���
			}
		}
		// ���н��̶��������
		if (finished_pcbs.size() == N) {
			cout << "\n���н������������\n";
			break;
		}
		clock++;		// ʱ��+1
		Sleep(666);
	}

	FreePCBs(pcbs);
	system("pause");
	return 0;
}
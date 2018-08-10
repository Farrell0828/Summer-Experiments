#include <iostream>
#include <queue>
#include <vector>
#include <random>
#include <ctime>
#include <Windows.h>
using namespace std;

// 状态枚举类型定义
enum State { ready, runnig, blocked, finished };

// 随机数发生器
default_random_engine e(time(nullptr));
uniform_int_distribution<> int_1_10(1, 10);
uniform_int_distribution<> int_1_5(1, 5);
uniform_int_distribution<> int_0_2;

// PCB结构体定义
struct PCB {
	int id;				// id
	State state;		// 状态
	int priority;		// 优先级，数值越大优先级越高
	int arrive_time;	// 到达时间
	int need_time;		// 需要运行总时间
	int used_time;		// 已经运行时间
};

// 初始化PCB
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

// 释放PCB空间
void FreePCBs(vector<PCB*>& pcbs) {
	for (auto x : pcbs) {
		delete x;
	}
}


// 展示PCB的详细信息
void ShowPCBInfo(const PCB* p) {
	cout << "\n进程ID: " << p->id << endl
		<< "  状态: " << p->state << endl
		<< "  优先级: " << p->priority << endl
		<< "  到达时间: " << p->arrive_time << endl
		<< "  需要运行时间: " << p->need_time << endl
		<< "  已经运行时间: " << p->used_time << endl;
}

// 根据进程状态和优先级从已到达进程中选出一个要运行的进程；
// 返回指向选中的进程PCB的指针，若已到达进程为空或无法选出返回空指针nullptr
PCB* ChooseOne(const vector<PCB*>& arrived_pcbs) {
	// 如果没有已到达进程
	if (arrived_pcbs.empty()) {
		return nullptr;
	}
	PCB* temp = nullptr;
	// 查看是否有就绪状态的进程
	for (auto x : arrived_pcbs) {
		// 如果有暂时将对应的PCB地址赋值给temp
		if (x->state == ready) {
			temp = x;
			break;
		}
	}
	// 如果temp == nullptr说明目前没有就绪状态的进程
	if (temp == nullptr) {
		return nullptr;
	}
	// 继续根据优先级等信息选择要运行的进程
	for (auto x : arrived_pcbs) {
		// 不是就绪状态的进程直接跳过
		if (x->state != ready) {
			continue;
		}
		// 如果当前进程x的优先级比choose_reault高，将x赋值给temp
		if (x->priority > temp->priority) {
			temp = x;
		}
		// 如果两进程优先级相同
		if (x->priority == temp->priority) {
			// 选先到达的那个
			if (x->arrive_time < temp->arrive_time) {
				temp = x;
			}
			// 如果到达时间也相同
			if (x->arrive_time == temp->arrive_time) {
				// 选剩余还需运行时间(总需运行时间need_time减去已使用CPU时间used_time)较小的那个
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

	vector<PCB*> arrived_pcbs;		// 记录已经到达的进程
	vector<PCB*> finished_pcbs;		// 记录结束的进程
	int clock = 1;					// 时钟时间
	bool cpu_running = false;		// cup状态
	PCB* running_pcb = nullptr;		// 指向正在运行的进程，为空表示没有进程正在运行
	while (true) {
		// 将此刻到达的进程列入arrived_pcbs
		cout << endl << clock << "时刻:\n";
		for (auto x : pcbs) {
			if (x->arrive_time == clock) {
				arrived_pcbs.push_back(x);
				cout << "  " << x->id << "号进程到达\n";
			}
		}
		// 如果此时没有进程在运行
		if (running_pcb == nullptr) {
			// 尝试从已到达进程中选着一个进程设置为运行进程
			running_pcb = ChooseOne(arrived_pcbs);
			if (running_pcb) {
				cout << "  " << running_pcb->id << "号进程开始运行\n";
			}
		}
		// 如果此时有进程在运行
		if (running_pcb) {
			running_pcb->used_time++;		// 已运行时间+1
			cout << "  " << running_pcb->id << "号进程运行中, 已运行"
				<< running_pcb->used_time << "单位时间, 共需运行"
				<< running_pcb->need_time << "单位时间" << endl;
			// 如果此进程运行结束
			if (running_pcb->used_time == running_pcb->need_time) {
				running_pcb->state = finished;	// 将此进程状态设置为完成
				finished_pcbs.push_back(running_pcb);	// 将此进程列入finished_pcbs
				cout << "  " << running_pcb->id << "号进程运行结束\n";
				running_pcb = nullptr;		// 将正在运行进程指向空
			}
		}
		// 所有进程都运行完成
		if (finished_pcbs.size() == N) {
			cout << "\n所有进程以运行完毕\n";
			break;
		}
		clock++;		// 时钟+1
		Sleep(666);
	}

	FreePCBs(pcbs);
	system("pause");
	return 0;
}
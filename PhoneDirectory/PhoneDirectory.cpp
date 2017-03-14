#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Err_Memory -1  //内存异常
#define Err_IllegalPos -2  //非法位置参数

#define Max_Size 500  //电话本最多存500个人
#define Increment_Size 100  //每次扩容可扩100个人

//定义每条记录的格式
typedef struct {
	char name[11];
	char department[15];
	char phone[9];  //固定电话
	char mobile[12];  //移动电话
}User;  //定义结构体为User

//用链表实现电话本
typedef struct {
	User *users;
	int user_num;  //已存入的用户数
	int book_size;  //电话本的总容量
}PhoneBook;

//构造一个空的电话本
int init_phone_book(PhoneBook *pb) {
	pb->users=(User*)malloc(sizeof(User)*Max_Size);  //分配内存空间
	if (!pb->users) {
		printf("内存异常，初始化电话本失败！\n");
		return Err_Memory;
	}
	pb->book_size = Max_Size;  //初始化总容量
	pb->user_num = 0;  //新电话本里面没有联系人
	return 0;
}

//清空电话本
int clear_phone_book(PhoneBook *pb) {
	pb->user_num = 0;
	return 0;
}

//测试电话本是否为空
bool is_empty(PhoneBook *pb) {
	return (pb->user_num==0);
}

//看电话本里存了多少人
int get_user_num(PhoneBook *pb) {
	return pb->user_num;
}

//遍历电话本
void traverse_book(PhoneBook *pb) {
	int i = 0;
	printf("所有联系人:%d\n",pb->user_num);
	for (i = 0; i < pb->user_num; i++) {
		printf("联系人%d:\t",i+1);
		printf("姓名：%s\t",pb->users[i].name);
		printf("单位：%s\t", pb->users[i].department);
		printf("电话：%s\t",pb->users[i].phone);
		printf("手机：%s\t", pb->users[i].mobile);
		printf("\n");
	}
}

//显示指定联系人信息
void show_user_infor(User u) {
	printf("姓名：%s\t", u.name);
	printf("单位：%s\t", u.department);
	printf("电话：%s\t", u.phone);
	printf("手机：%s\t", u.mobile);
	printf("\n");
}

//一会儿试一下input_user，返回一个User类型的指针***********************************************

//在指定位置插入新联系人
int insert_new_user(PhoneBook *pb, User new_user, int p) {
	//合法插入位置为1 ~ pb->user_num+1
	if (p<1 || p>pb->user_num + 1) {  //非法插入位置
		printf("非法插入位置！不能添加新联系人\n");
		return Err_IllegalPos;
	}
	if (pb->user_num == pb->book_size) {  //电话本写满了
		User *newusers=(User*)realloc(pb->users,sizeof(User)*(pb->book_size+Increment_Size));
		if (!newusers) {
			printf("内存分配异常，不能扩展电话本！\n");
			return Err_Memory;
		}
	}
	//添加新联系人
	int i = 0;
	for (i = pb->user_num - 1; i >= p - 1; i--) {
		pb->users[i + 1] = pb->users[i];
	}
	pb->users[p - 1] = new_user;
	pb->user_num++;
	printf("新联系人添加成功！\n");
	return 0;
}

//删除指定位置的联系人
int delete_user(PhoneBook *pb, int p, User *target_user) {
	if (p<1 || p>pb->user_num) {
		printf("非法位置，不能删除联系人！\n");
		return Err_IllegalPos;
	}
	//存储要删除的用户
	*target_user = pb->users[p-1];
	int i = 0;
	for (i = p ; i <pb->user_num; i++) {
		pb->users[i - 1] = pb->users[i];
	}
	pb->user_num--;
	printf("删除联系人成功！\n");
	return 0;
}

//定位联系人位置
int locate_user(PhoneBook *pb,User target_user) {
	int i = 0;
	for (i = 0; i < pb->user_num; i++) {
		//比较联系人姓名
		if (strcmp(pb->users[i].name, target_user.name) == 0) {
			return i + 1;
		}
	}
	printf("未能查找到联系人！\n");
	return 0;
}

//获取指定位置的联系人
int get_user(PhoneBook *pb, int p,User *target_user) {
	if (p<1 || p>pb->user_num) {
		printf("非法位置，不能获取该联系人信息！\n");
	}
	*target_user = pb->users[p-1];
	return 0;
}

void welcome() {
	printf("\t\t\t**********电话本管理***********\n");
	printf("\t\t\t*******************************\n");
}

int main() {
	welcome();

	int choice;  //接收用户输入的菜单选项
	User my_user;
	User *target = (User*)malloc(sizeof(User));  //target用于存储取得的user
	int result = 0;  //接收函数的返回值

	//初始化一个电话本
	PhoneBook *my_pb=(PhoneBook*)malloc(sizeof(PhoneBook));
	//初始化失败，退出程序
	if (init_phone_book(my_pb) != 0)
		return 0;	

	while (true) {
		printf("1.浏览联系人\t 2.查找联系人\t 3.新增联系人\t 4.删除联系人\t 5.退出电话本\n");
		printf("请输入1-5：");
		scanf_s("%d",&choice);
		switch (choice) {
			case 1:
				printf("\t\t\t查看所有联系人信息\n");
				traverse_book(my_pb);
				printf("\n");
				printf("******************************************************************************\n");
				break;
			case 2:
				printf("\t\t\t查找联系人\n");
				//按姓名查找联系人
				printf("请输入要查找的联系人姓名（最多10个字符）：");
				scanf_s("%s", my_user.name,(unsigned)_countof(my_user.name));
				printf("联系人%s的查找结果：\n",my_user.name);
				result = locate_user(my_pb, my_user);
				if (result > 0) {   //查找到了目标用户
					get_user(my_pb,result,target);
					show_user_infor(*target);
				}
				printf("\n");
				printf("******************************************************************************\n");
				break;
			case 3:
				printf("\t\t\t新增联系人\n");
				//新增联系人
				printf("请输入姓名（最多10个字符）：");
				scanf_s("%s",my_user.name,(unsigned)_countof(my_user.name));
				printf("请输入单位（最多14个字符）：");
				scanf_s("%s",my_user.department,(unsigned)_countof(my_user.department));
				printf("请输入固定电话（最多8个字符）：");
				scanf_s("%s",my_user.phone,(unsigned)_countof(my_user.phone));
				printf("请输入移动电话（最多11个字符）：");
				scanf_s("%s",my_user.mobile,(unsigned)_countof(my_user.mobile));
				//默认在电话本最后添加新联系人
				insert_new_user(my_pb,my_user,my_pb->user_num+1);
				printf("\n");
				printf("******************************************************************************\n");
				break;
			case 4:
				printf("\t\t\t删除联系人\n");
				printf("请输入要删除联系人的姓名：");
				scanf_s("%s",my_user.name,(unsigned)_countof(my_user.name));
				result=locate_user(my_pb,my_user);
				if (result > 0) {
					//查找到该联系人
					delete_user(my_pb,result,target);
				}
				printf("\n");
				printf("******************************************************************************\n");
				break;
			case 5:
				printf("已退出电话本程序！\n");
				printf("\n");
				printf("******************************************************************************\n");
				system("pause");
				return 0;
			default:
				printf("菜单选择错误，请重新输入！\n");
				printf("\n");
				printf("******************************************************************************\n");
		}
	}
	return 0;
}
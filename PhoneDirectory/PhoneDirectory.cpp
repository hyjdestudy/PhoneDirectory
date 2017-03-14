#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Err_Memory -1  //�ڴ��쳣
#define Err_IllegalPos -2  //�Ƿ�λ�ò���

#define Max_Size 500  //�绰������500����
#define Increment_Size 100  //ÿ�����ݿ���100����

//����ÿ����¼�ĸ�ʽ
typedef struct {
	char name[11];
	char department[15];
	char phone[9];  //�̶��绰
	char mobile[12];  //�ƶ��绰
}User;  //����ṹ��ΪUser

//������ʵ�ֵ绰��
typedef struct {
	User *users;
	int user_num;  //�Ѵ�����û���
	int book_size;  //�绰����������
}PhoneBook;

//����һ���յĵ绰��
int init_phone_book(PhoneBook *pb) {
	pb->users=(User*)malloc(sizeof(User)*Max_Size);  //�����ڴ�ռ�
	if (!pb->users) {
		printf("�ڴ��쳣����ʼ���绰��ʧ�ܣ�\n");
		return Err_Memory;
	}
	pb->book_size = Max_Size;  //��ʼ��������
	pb->user_num = 0;  //�µ绰������û����ϵ��
	return 0;
}

//��յ绰��
int clear_phone_book(PhoneBook *pb) {
	pb->user_num = 0;
	return 0;
}

//���Ե绰���Ƿ�Ϊ��
bool is_empty(PhoneBook *pb) {
	return (pb->user_num==0);
}

//���绰������˶�����
int get_user_num(PhoneBook *pb) {
	return pb->user_num;
}

//�����绰��
void traverse_book(PhoneBook *pb) {
	int i = 0;
	printf("������ϵ��:%d\n",pb->user_num);
	for (i = 0; i < pb->user_num; i++) {
		printf("��ϵ��%d:\t",i+1);
		printf("������%s\t",pb->users[i].name);
		printf("��λ��%s\t", pb->users[i].department);
		printf("�绰��%s\t",pb->users[i].phone);
		printf("�ֻ���%s\t", pb->users[i].mobile);
		printf("\n");
	}
}

//��ʾָ����ϵ����Ϣ
void show_user_infor(User u) {
	printf("������%s\t", u.name);
	printf("��λ��%s\t", u.department);
	printf("�绰��%s\t", u.phone);
	printf("�ֻ���%s\t", u.mobile);
	printf("\n");
}

//һ�����һ��input_user������һ��User���͵�ָ��***********************************************

//��ָ��λ�ò�������ϵ��
int insert_new_user(PhoneBook *pb, User new_user, int p) {
	//�Ϸ�����λ��Ϊ1 ~ pb->user_num+1
	if (p<1 || p>pb->user_num + 1) {  //�Ƿ�����λ��
		printf("�Ƿ�����λ�ã������������ϵ��\n");
		return Err_IllegalPos;
	}
	if (pb->user_num == pb->book_size) {  //�绰��д����
		User *newusers=(User*)realloc(pb->users,sizeof(User)*(pb->book_size+Increment_Size));
		if (!newusers) {
			printf("�ڴ�����쳣��������չ�绰����\n");
			return Err_Memory;
		}
	}
	//�������ϵ��
	int i = 0;
	for (i = pb->user_num - 1; i >= p - 1; i--) {
		pb->users[i + 1] = pb->users[i];
	}
	pb->users[p - 1] = new_user;
	pb->user_num++;
	printf("����ϵ����ӳɹ���\n");
	return 0;
}

//ɾ��ָ��λ�õ���ϵ��
int delete_user(PhoneBook *pb, int p, User *target_user) {
	if (p<1 || p>pb->user_num) {
		printf("�Ƿ�λ�ã�����ɾ����ϵ�ˣ�\n");
		return Err_IllegalPos;
	}
	//�洢Ҫɾ�����û�
	*target_user = pb->users[p-1];
	int i = 0;
	for (i = p ; i <pb->user_num; i++) {
		pb->users[i - 1] = pb->users[i];
	}
	pb->user_num--;
	printf("ɾ����ϵ�˳ɹ���\n");
	return 0;
}

//��λ��ϵ��λ��
int locate_user(PhoneBook *pb,User target_user) {
	int i = 0;
	for (i = 0; i < pb->user_num; i++) {
		//�Ƚ���ϵ������
		if (strcmp(pb->users[i].name, target_user.name) == 0) {
			return i + 1;
		}
	}
	printf("δ�ܲ��ҵ���ϵ�ˣ�\n");
	return 0;
}

//��ȡָ��λ�õ���ϵ��
int get_user(PhoneBook *pb, int p,User *target_user) {
	if (p<1 || p>pb->user_num) {
		printf("�Ƿ�λ�ã����ܻ�ȡ����ϵ����Ϣ��\n");
	}
	*target_user = pb->users[p-1];
	return 0;
}

void welcome() {
	printf("\t\t\t**********�绰������***********\n");
	printf("\t\t\t*******************************\n");
}

int main() {
	welcome();

	int choice;  //�����û�����Ĳ˵�ѡ��
	User my_user;
	User *target = (User*)malloc(sizeof(User));  //target���ڴ洢ȡ�õ�user
	int result = 0;  //���պ����ķ���ֵ

	//��ʼ��һ���绰��
	PhoneBook *my_pb=(PhoneBook*)malloc(sizeof(PhoneBook));
	//��ʼ��ʧ�ܣ��˳�����
	if (init_phone_book(my_pb) != 0)
		return 0;	

	while (true) {
		printf("1.�����ϵ��\t 2.������ϵ��\t 3.������ϵ��\t 4.ɾ����ϵ��\t 5.�˳��绰��\n");
		printf("������1-5��");
		scanf_s("%d",&choice);
		switch (choice) {
			case 1:
				printf("\t\t\t�鿴������ϵ����Ϣ\n");
				traverse_book(my_pb);
				printf("\n");
				printf("******************************************************************************\n");
				break;
			case 2:
				printf("\t\t\t������ϵ��\n");
				//������������ϵ��
				printf("������Ҫ���ҵ���ϵ�����������10���ַ�����");
				scanf_s("%s", my_user.name,(unsigned)_countof(my_user.name));
				printf("��ϵ��%s�Ĳ��ҽ����\n",my_user.name);
				result = locate_user(my_pb, my_user);
				if (result > 0) {   //���ҵ���Ŀ���û�
					get_user(my_pb,result,target);
					show_user_infor(*target);
				}
				printf("\n");
				printf("******************************************************************************\n");
				break;
			case 3:
				printf("\t\t\t������ϵ��\n");
				//������ϵ��
				printf("���������������10���ַ�����");
				scanf_s("%s",my_user.name,(unsigned)_countof(my_user.name));
				printf("�����뵥λ�����14���ַ�����");
				scanf_s("%s",my_user.department,(unsigned)_countof(my_user.department));
				printf("������̶��绰�����8���ַ�����");
				scanf_s("%s",my_user.phone,(unsigned)_countof(my_user.phone));
				printf("�������ƶ��绰�����11���ַ�����");
				scanf_s("%s",my_user.mobile,(unsigned)_countof(my_user.mobile));
				//Ĭ���ڵ绰������������ϵ��
				insert_new_user(my_pb,my_user,my_pb->user_num+1);
				printf("\n");
				printf("******************************************************************************\n");
				break;
			case 4:
				printf("\t\t\tɾ����ϵ��\n");
				printf("������Ҫɾ����ϵ�˵�������");
				scanf_s("%s",my_user.name,(unsigned)_countof(my_user.name));
				result=locate_user(my_pb,my_user);
				if (result > 0) {
					//���ҵ�����ϵ��
					delete_user(my_pb,result,target);
				}
				printf("\n");
				printf("******************************************************************************\n");
				break;
			case 5:
				printf("���˳��绰������\n");
				printf("\n");
				printf("******************************************************************************\n");
				system("pause");
				return 0;
			default:
				printf("�˵�ѡ��������������룡\n");
				printf("\n");
				printf("******************************************************************************\n");
		}
	}
	return 0;
}
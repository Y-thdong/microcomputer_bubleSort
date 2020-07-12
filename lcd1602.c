#include"reg52.h"		
#include <stdio.h>			 
#define uint unsigned int
#define uchar unsigned char
sbit key0=P2^6;  //S0
sbit key1=P2^7;  //S1
sbit key2=P3^0;  //S2
sbit key3=P3^1;  //S3
sbit key4=P3^2;  //S4
sbit key5=P3^3;  //S5
sbit key6=P3^4;  //S6
sbit key7=P3^5;  //S7
sbit key8=P3^6;  //S8
sbit key9=P3^7;  //S9
sbit keysort=P2^5; 	//��С����
sbit keyreve=P2^4; 	//�Ӵ�С
sbit mark=P1^7;
uint markd=0;

sbit RS=P1^0;
sbit RW=P1^1;
sbit RE=P1^2;
uchar str1[]={"Cin"};
uchar str2[]={"Sort"};
uchar str3[]={"Reverse"}; 
uchar str4[]={"End Input"};
uint arr[]={0,0,0,0,0,0};//�洢���ݵ�����			 
uint count=0;	//��ת
uint temp=0;
uint down=0;

void delay(uint t)
{
	uint i=0,j=0;
	for(i=0;i<t;i++)
	{
		for(j=0;j<120;j++);
	}
}

void writedat(uchar dat)
{
	RS=1;
	RW=0;
	RE=0;
	P0=dat;
	delay(5);
	RE=1;
	RE=0;
}

void writecom(uchar com)
{
	RS=0;
	RW=0;
	RE=0;
	P0=com;
	delay(5);
	RE=1;
	RE=0;
}

void initlcd()
{
	writecom(0x38);
	writecom(0x0c);
	writecom(0x06);
	writecom(0x01);
}

void display(uchar str)
{
	uint i=0;
	writecom(0x80);
	delay(5);
	writedat(str);
	delay(5);
}

void displayCin(){
	uint i=0;
	writecom(0x80);
	delay(5);
	while(str1[i]!='\0')
	{
		writedat(str1[i]);
		delay(5);
		i++;
	}
}
void displaySort(){
	uint i=0;
	writecom(0x80);
	delay(5);
	while(str2[i]!='\0')
	{
		writedat(str2[i]);
		delay(5);
		i++;
	}
}
void displayReverse(){
	uint i=0;
	writecom(0x80);
	delay(5);
	while(str3[i]!='\0')
	{
		writedat(str3[i]);
		delay(5);
		i++;
	}
}
void displayOK(){
	uint i=0;
	delay(5);
	while(str4[i]!='\0')
	{
		writedat(str4[i]);
		delay(5);
		i++;
	}
}
void inpurArr(uint count){	//��������
	if(arr[temp]<10&&arr[temp]!=0){	  //˵����λ��ֻ���˸�λ
		arr[temp]=count+arr[temp]*10;	  	//��һ�������ǰ�����ʹ����ˣ���temp++ָ����һλ
		temp++;
		writedat(' ');
		if(temp==5){markd=1;}//++֮��temp==5��˵�������һλ��,ע�����ﲻ��mark
	}
	else{
	 	arr[temp]=count;
	}
}

void bubble_sort(uint len)//nΪ����a��Ԫ�ظ���
{
    uint i, j, tmp;
    for (i = 0; i < len - 1; i++)
        for (j = 0; j < len - 1 - i; j++)
            if (arr[j] > arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
}
void reserve1(uint n){ //nΪ����a��Ԫ�ظ���
	uint m=(n+1)/2;
	uint i=0;
	for(i;i<m;i++){
	  uint j=n-1-i;
	  uint temp=arr[i];
	      arr[i]=arr[j];
	      arr[j]=temp;
	}
}
void writedown(){
	writecom(0xc0);
	down++;
}
void displayLcd(){
	uint f=0;
	down=0;		 //�ٴΰ�down=0
	 while(f<=11){
	 if(f<=9){
	 //	arr[f%2==1?(f-1)/2:f/2];//�����㴦����Ǹ�����Ԫ��
		if(f%2==1){
		//(f-1)/2���������λ��
		//arr[f%2==1?(f-1)/2:f/2]
		writedat(arr[(f-1)/2]%10+0x30);
		writedat(' ');
		f++;
		}else{		//��ʱ���ʾ������ǵ�ǰԪ�ص�ʮλ
			writedat(arr[f/2]/10+0x30);
			f++;
		}
	 }
	 else{	//��ʱҺ����Ҫ����
	 	if(down==0){writedown();}
		 if(f%2==1){
		writedat(arr[(f-1)/2]%10+0x30);
		writedat(' ');
		f++;
		}else{		//��ʱ���ʾ������ǵ�ǰԪ�ص�ʮλ
			writedat(arr[f/2]/10+0x30);
			f++;
		}
	}	 
	 }
}


void main()
{
	
	mark=0;		   //mark�������ְ����Ƿ񱻰���
	initlcd();
	while(1){
		displayCin();
		if(mark==1){	 //��ʼ����Ͳ���ʾ�����ı�
			break;
		}
	}

	initlcd();	  

	/****�û�����******/
	while(1){
		if(key0==0)
		{
			count=0;
			delay(500);
			if(temp>=5&&markd==1){if(down==0){writedown();}writedat('0');}	 //markd�Ǹ�ɶ�ģ�
			else{writedat('0');}	 
			inpurArr(count);	//�ж���ô��
		}
		/*
			void writedown(){
				writecom(0xc0);
				down++;
			}
		*/
		else if(key1==0)
		{
			count=1;
			delay(500);	  
			if(temp>=5&&markd==1){if(down==0){writedown();};writedat('1');}
			else{writedat('1');}	 
			inpurArr(count);	//�ж���ô��
		}
		else if(key2==0)
		{
			count=2;
			delay(500);	 
			if(temp>=5&&markd==1){if(down==0){writedown();}writedat('2');}
			else{writedat('2');}	  
			inpurArr(count);	//�ж���ô��
		}
		else if(key3==0)
		{
			count=3;
			delay(500);
			if(temp>=5&&markd==1){if(down==0){writedown();}writedat('3');}
			else{writedat('3');}	  
			inpurArr(count);	//�ж���ô��
		}
		else if(key4==0)
		{
			count=4;
			delay(500);	 
			if(temp>=5&&markd==1){if(down==0){writedown();}writedat('4');}
			else{writedat('4');}	   
			inpurArr(count);	//�ж���ô��
		}
		else if(key5==0)
		{
			count=5;
			delay(500);	  
			if(temp>=5&&markd==1){if(down==0){writedown();}writedat('5');}
			else{writedat('5');}
			inpurArr(count);
		}
		else if(key6==0)
		{
			count=6;
			delay(500);	  
			if(temp>=5&&markd==1){if(down==0){writedown();}writedat('6');}
			else{writedat('6');}	 
			inpurArr(count);	//�ж���ô��
		}
		else if(key7==0)
		{
			count=7;
			delay(500);	  
			if(temp>=5&&markd==1){if(down==0){writedown();}writedat('7');}
			else{writedat('7');} 
			inpurArr(count);
		}
		else if(key8==0)
		{
			count=8;
			delay(500);	  
			if(temp>=5&&markd==1){if(down==0){writedown();}writedat('8');}
			else{writedat('8');}	 
			inpurArr(count);	//�ж���ô��
		}
		else if(key9==0)
		{
			count=9;
			delay(500);	 
			if(temp>=5&&markd==1){if(down==0){writedown();}writedat('9');}
			else{writedat('9');}	 
			inpurArr(count);	//�ж���ô��
		}
		if(temp==6)		//�������
		{
			delay(500);
			writecom(0xc0);displayOK();delay(3000);
			break;
		}	
	}


	/****������ϣ���ʼ����ֱ�����*****/

	while(1){
			/*****��������******/
		if(keysort==0){
			initlcd();
			displaySort();	 //��ʾsort
			delay(200);
			bubble_sort(6);
			initlcd();
			displayLcd();
			delay(3000);
		}
		/*******��������********/
		if(keyreve==0){
			initlcd();	
			bubble_sort(6);
			displayReverse();  //��ʾreverse
			delay(2000);
			reserve1(6);
			initlcd();	  
			displayLcd();
			delay(3000);
		}
	}
	
	

}

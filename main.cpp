//
//  main.cpp
//  SortAlogrithm
//
//  Created by glyang on 16/8/22.
//  Copyright © 2016年 glyang. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;
struct Node
{
    double value;
    Node *next;
    //Node(double x) : value(x), next(NULL) {};
};
//插入排序
void insertSort(vector<int> &arr){
    for(int i=1;i<arr.size();i++){
        for(int j=i;j>0;j--){
            if (arr[j]<arr[j-1]) {
                int temp = arr[j];
                arr[j]=arr[j-1];
                arr[j-1]=temp;
            }
        }
    }
}
//冒泡排序
void bubbleSort(vector<int> &arr){
    for(int i=0;i<arr.size()-1;i++){
        for(int j=0;j<arr.size()-i-1;j++){
            if (arr[j]>arr[j+1]) {
                int tmp=arr[j+1];
                arr[j+1]=arr[j];
                arr[j]=tmp;
            }
        }
    }
}
//选择排序
void selectSort(vector<int> &arr){
    
    for(int i=0;i<arr.size();i++){
        int min=i;
        for (int j=i+1; j<arr.size(); j++) {
            if(arr[j]<arr[min])
                min=j;
        }
        int tmp=arr[min];
        arr[min]=arr[i];
        arr[i]=tmp;
    }
}
//希尔排序
void shellSort(vector<int> &arr){
    for (int step=(int)arr.size()>>1; step>0; step>>=1) {  //步长n/2,每次减半
        for (int i=step; i<arr.size(); i++) {  //从第step个数向后遍历所有数，因为前step个数（一个数字本来就是有序的）
            int temp=arr[i]; //先保存要比较的第i个数
            int j=i-step;
            for (;j>=0&&arr[j]>temp; j-=step){ //从第i-step数开始，比较与要插入数arr[i]的大小，弱大于arr[i],覆盖该数arr[j+step]=arr[j];循环比较前一个数跟前前一个数，还是跟temp比较（将temp插入到合适的位置，所以是一直跟temp比较）
                arr[j+step]=arr[j];
            }
            arr[j+step]=temp; //将temp中的数插入到arr[j+step]位置
            
        }
    }
}
//归并排序
void merge_array(vector<int> &arr, int s, int m, int e, vector<int> &temp)
{
    int ls = s, rs = m, ts = s;
    while (ls != m && rs != e)  //合并s-m ,m-e,存入临时数组temp
        if (arr[ls] < arr[rs])
            temp[ts++] = arr[ls++];
        else
            temp[ts++] = arr[rs++];
    
    while (ls < m)  //只剩左边矩阵
        temp[ts++] = arr[ls++];
    
    while (rs < e)  //只剩右边矩阵
        temp[ts++] = arr[rs++];
    
    for (int i = s;i < e; i++)  //把临时数组的值给arr
        arr[i] = temp[i];
}
void merge_sort(vector<int> &arr, int s, int e, vector<int> &temp)
{
    int m = (s + e) / 2;
    if (m != s) {
        merge_sort(arr, s, m, temp); //下标是正确的
        merge_sort(arr, m, e, temp);
        merge_array(arr, s, m, e, temp);
    }
}
void mergeSort(vector<int> &arr){
    vector<int> temp(arr); //辅助数组
    merge_sort(arr,0,(int)arr.size(),temp); //b为0，e为arr.size()
}
//快排
void quickSort(vector<int> &arr,int s,int e){ //初次调用 e为arr.size()-1,s为0
    if (s<e){
        int i=s,j=e,x=arr[s];  //选取第一个数为基数，x保存第一个数
        while (i<j) { //将大的放在后边，小的放在前边
            while (i<j&&arr[j]>=x) { //从后往前找比基数小的
                j--;
            }
            if (i<j)
                arr[i++]=arr[j];  //交换小的跟arr[i]位置的数，i++
            while (i<j&&arr[i]<x) { //从前往后找比基数大的
                i++;
            }
            if (i<j)
                arr[j--]=arr[i]; //交换大的跟arr[j]位置的数，j--
        }
        arr[i]=x; //最后i=j，把基数x，放在i处
        quickSort(arr, s, i-1); //迭代i之前
        quickSort(arr, i+1, e); //迭代i之后
    }
}
//堆排序
void adjustHeap(vector<int> &arr,int p,int len){
    int curParent=arr[p];
    int child=2*p+1;
    while (child<len) {
        if (child+1<len&&arr[child]<arr[child+1])  //child+1为右节点
            child++; //child保存的是较大的孩子下标
        if (curParent<arr[child]) { //根节点比子节点小，交换
            arr[p]=arr[child];
            p=child;  //将子节点调整成当前根节点，继续调整
            child=2*p+1;
        }else
            break;
    }
    arr[p]=curParent; //将p（p=child是之前的child）位置的值改为之前的arr[p]
}
void heapSort(vector<int> &arr){
    int n=(int)arr.size();
    for (int i=n/2-1; i>=0; i--)
        adjustHeap(arr,i,n);  //从第一个不是叶子节点的节点开始调整堆
    for (int i=n-1; i>=0; i--) { //从长度为n的堆，一步步到长度为1,停止
        int max=arr[0];
        arr[0]=arr[i]; //交换堆顶与最后元素
        arr[i]=max;
        adjustHeap(arr, 0, i); //调整节点0，此时堆的长度为i
    }
}
//计数排序arr，申请一个0~max的数组A，统计数组arr中为0~max下标出现的次数存入A，从前到后累加（数组A中的值代表将要放入排序位置的下标），
//从后往前遍历数组，将arr中的值放入C[A[arr[i]]]位置，并且A[arr[i]]-1,C为最终排序数组
//  只能排序0~k的数，所以适用于小整数
void countSort(vector<int> &arr){
    int n=(int)arr.size();
    //找出数组中最大的数
    int max=arr[0];
    for(int i=1;i<n;i++){
        if (arr[i]>max){
            max=arr[i];
        }
    }
    vector<int> A(max+1);
    vector<int> C(n);
    for (int i=0; i<n; i++) //统计个数
        A[arr[i]]++;
    for (int i=1; i<=max; i++) //累加
        A[i]+=A[i-1];
    for (int i=n-1; i>=0; i--){
        C[A[arr[i]]-1]=arr[i]; //将arr[i]放入合适位置，
        A[arr[i]]--;  //下一相同数位置--
    }
    arr=C;
    
}
/* 更合理的实现
 int* countingSort(int* A, int n) {
 // write code here
 if(A ==NULL || n <2){
 return NULL;
 }
 int min = A[0];
 int max = A[0];
 for(int i = 0; i < n; i++){
 min= min<=A[i]? min:A[i];
 max= max>=A[i]? max:A[i];
 }
 int len = max - min + 1;
 vector<int> countArr(len, 0);
 for(int i=0; i < n; i++){
 countArr[A[i] - min]++;
 }
 int index = 0;
 for(int i=0; i < len; i++){
 while(countArr[i]-- > 0){
 A[index++] = i + min;
 }
 }
 return A;
 }*/
//基数排序 在基数排序的基础上
int maxBit(int* A,int n){ //找出最长的位数
    int mb=0;
    for (int i=0; i<n; i++) {
        int p=A[i];
        int c=1;
        while (p/10) {
            p=p/10;
            c++; //位数加1
        }
        if(c>mb)
            mb=c;
    }
    return mb;
}
void radixSort(int *A,int n){
    int count[10],tmp[10];
    int mb=maxBit(A, n);
    int r=1;
    for (int j=0; j<mb; j++) {  //从最低位到最高位
        for(int i=0;i<10;i++){//装桶之前要先清桶[0-9]
            count[i]=0;
        }
        for(int i=0;i<n;i++) //记录每个桶的记录数=统计个数
        {
            int k=A[i]/r;
            int q=k%10;
            count[q]++;
        }
        for(int i=1;i<10;i++)//累加
        {
            count[i]+=count[i-1];
        }
        for(int i=n-1;i>=0;i--)
        {
            int p=A[i]/r;
            int s=p%10;
            tmp[count[s]-1]=A[i]; //tmp临时变量
            count[s]--;
        }
        for(int i=0;i<n;i++)
        {
            A[i]=tmp[i];
        }
        r=r*10;//r控制位数
    }
}
//桶排序
void bucketSort(double* arr, int length)
{
    Node key[10];
    int number = 0;
    Node *p, *q;//插入节点临时变量
    int counter = 0;
    for(int i = 0; i < 10; i++)
    {
        key[i].value = 0;
        key[i].next = NULL;
    }
    for(int i = 0; i < length; i++)
    {
        Node *insert=new Node();
        insert->value = arr[i];
        insert->next = NULL;
        number = arr[i] * 10;
        if(key[number].next == NULL)
        {
            key[number].next = insert;
        }else{
            p = &key[number];
            q = key[number].next;
            while((q != NULL) && (q->value <= arr[i]))
            {
                q = q->next;
                p = p->next;
            }
            insert->next = q;
            p->next = insert;
        }
    }
    for(int i = 0; i < 10; i++)
    {
        p = key[i].next;
        if(p == NULL)
            continue;
        while(p != NULL)
        {
            arr[counter++] = p->value;
            p = p->next;
        }
    }
}
/*
 ListNode *insertSortList(ListNode *head) {
 if (head==NULL||head->next==NULL) {
 return head;
 }
 ListNode *dummy = new ListNode(0);
 // 这个dummy的作用是，把head开头的链表一个个的插入到dummy开头的链表里
 // 所以这里不需要dummy->next = head;
 
 while (head != NULL) {
 ListNode *temp = dummy;
 ListNode *next = head->next;
 while (temp->next != NULL && temp->next->val < head->val) {
 temp = temp->next;
 }
 head->next = temp->next;
 temp->next = head;
 head = next;
 }
 
 return dummy->next;
 }
 */
int main()
{   double A[5]={100,99.0,103,1002,200};
    
    //vector<int> a={2,3,1,7,2};
    bucketSort(A, 5);
    //for(vector<int>::iterator i=a.begin();i!=a.end();++i){
    //    cout<<*i;
    //}
    return 0;
}


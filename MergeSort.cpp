#include <iostream>
#include <vector>
using namespace std;

void merge(vector <int> &leftArray, vector <int> &rightArray, vector <int> &array){
    int lefsize = leftArray.size();
    int rightSize = rightArray.size();
    int i = 0;
    int l = 0;
    int r = 0;

    while(l < lefsize && r < rightSize){
        /*Cuando validamos que nuestro elemento de la izquierda es menor lo almacenamos en nuestro 
        nuevo arreglo
        */
        if(leftArray[l] < rightArray[r]){
            array[i] = leftArray[l];
            i++;
            l++;
        }else{
            array[i] = rightArray[r];
            i++;
            r++;
        }

    }   
    while(l < lefsize){
        array[i] = leftArray[l];
        i++;
        l++;

    }
    while (r < rightSize){
        array[i] = rightArray[r];
        i++;
        r++;
    }

}
void mergeSort(vector <int> &array){
    int n = array.size();
    if(n<=1){ //Caso base
        return;
    }
    int center = n/2;

    //Crear arreglo izquierdo y derecho con el size de los elementos
    vector <int> leftArray(center);
    vector <int> rightArray(n-center);
    
    for(int i = 0; i < n; i++){
        if(i < center){
            leftArray[i] = array[i];
        }else{
            rightArray[i-center] = array[i];
        }

    }
    //..........................Dividir.................................
    mergeSort(leftArray);
    mergeSort(rightArray);

    //.................................Conquer.............................
    merge(leftArray, rightArray, array);



}

int main(){
    vector <int> array = {12,3,7,9,14,6,11,2};
    mergeSort(array);
    for(int num:array){
        cout << num << " ";
    }

}
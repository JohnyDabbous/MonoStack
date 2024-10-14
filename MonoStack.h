#ifndef MonoStack_H
#define MonoStack_H
//basically the same thing as the TStack we made in class
template <typename T>
class monoStack{
    public:
        public:
        monoStack(int numOfElements, char incOrDinc);
        ~monoStack();
        void push(T c); 
        T pop(); 
        T peek(); 
        bool isFull();
        bool isEmpty();
        int size();
        char getChar();

    private:
        T* stackArr;
        int count; 
        int maxSize; 
        int top; 
        char o;
    
};

template <typename T>
monoStack<T>::monoStack(int numOfElements, char incOrDince){
    stackArr = new T[numOfElements];
    count = 0;
    maxSize = numOfElements;
    top = -1;
    o = incOrDince;
}

template <typename T>
monoStack<T>::~monoStack(){
    delete[] stackArr;
}

//only thing that changed basically
template <typename T>
void monoStack<T>::push(T c){
    if (isFull()){
        T* tempArr = new T[2*maxSize];
        for(int i = 0; i < maxSize; ++i){
            tempArr[i] = stackArr[i];
        }
        maxSize = maxSize * 2;
        delete[] stackArr;
        stackArr = tempArr;
    }

    if (o == 'i') {  //increasing
        while (top >= 0 && stackArr[top] >= c) {
            this->pop();
        }
    } 
    else {  //decreasing
        while (!(isEmpty() && (peek() <= c))) {
            this->pop();
        }
    }

    stackArr[++top] = c; 
    ++count;
}

template <typename T>
bool monoStack<T>::isEmpty(){
    return (count == 0);
}

template <typename T>
bool monoStack<T>::isFull(){
    if (count == maxSize){
        return true;
    }
    return false;
}

template <typename T>
int monoStack<T>::size(){
    return count;
}

template <typename T>
T monoStack<T>::pop(){
    --count;
    return stackArr[top--];
}

template <typename T>
T monoStack<T>::peek(){
    return stackArr[top];
}

template <typename T>
char monoStack<T>::getChar(){
    return this->o;
}

#endif
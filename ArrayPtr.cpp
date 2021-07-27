#include <cassert>
#include <cstdlib>

template <typename Type>
class ArrayPtr {
public:
    // �������������� ArrayPtr ������� ����������
    ArrayPtr() = default;

    // ������ � ���� ������ �� size ��������� ���� Type.
    // ���� size == 0, ���� raw_ptr_ ������ ���� ����� nullptr
    explicit ArrayPtr(size_t size) 
    {          
        if (size == 0)
        {
            raw_ptr_ = nullptr;
        }
        else
        {
            raw_ptr_ = new Type[size];
        }
    }

    // ����������� �� ������ ���������, ��������� ����� ������� � ���� ���� nullptr
    explicit ArrayPtr(Type* raw_ptr) noexcept 
    {
        raw_ptr_ = raw_ptr;
    }

    // ��������� �����������
    ArrayPtr(const ArrayPtr&) = delete;

    ~ArrayPtr()
    {
        delete[] raw_ptr_;
    }

    // ��������� ������������
    ArrayPtr& operator=(const ArrayPtr&) = delete;

    // ���������� ��������� �������� � ������, ���������� �������� ������ �������
    // ����� ������ ������ ��������� �� ������ ������ ����������
    [[nodiscard]] Type* Release() noexcept 
    {
        Type* temp_ptr = raw_ptr_;
        raw_ptr_ = nullptr;
        return temp_ptr;
    }

    // ���������� ������ �� ������� ������� � �������� index
    Type& operator[](size_t index) noexcept 
    {
        return *(raw_ptr_ + index);
    }

    // ���������� ����������� ������ �� ������� ������� � �������� index
    const Type& operator[](size_t index) const noexcept 
    {
        return *(raw_ptr_ + index);
    }

    // ���������� true, ���� ��������� ���������, � false � ��������� ������
    explicit operator bool() const 
    {     
        bool result = false;
        if (raw_ptr_)
        {
            result = true;
        }
        return result;
    }

    // ���������� �������� ������ ���������, ��������� ����� ������ �������
    Type* Get() const noexcept 
    {        
        return raw_ptr_;
    }

    // ������������ ��������� ��������� �� ������ � �������� other
    void swap(ArrayPtr& other) noexcept 
    {   
        Type* temp;
        temp = other.Get();
        other.raw_ptr_ = raw_ptr_;
        raw_ptr_ = temp;
    }

private:
    Type* raw_ptr_ = nullptr;
    
};

int main() {
    ArrayPtr<int> numbers(10);
    const auto& const_numbers = numbers;

    numbers[2] = 42;
    assert(const_numbers[2] == 42);
    assert(&const_numbers[2] == &numbers[2]);

    assert(numbers.Get() == &numbers[0]);

    ArrayPtr<int> numbers_2(5);
    numbers_2[2] = 43;

    numbers.swap(numbers_2);

    assert(numbers_2[2] == 42);
    assert(numbers[2] == 43);
    return 0;
}
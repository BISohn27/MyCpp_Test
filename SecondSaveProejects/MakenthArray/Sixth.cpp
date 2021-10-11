#include <iostream>

namespace Myarray
{

	class Array;
	class Int;
	class Iterator;

	class Array
	{
	friend Int;

	private:
		const int dim;
		int *size;

		struct Address
		{
			int level;

			void *next;
		};

		Address *top;

	public:
		Array(int dim_in, int *array_size) :dim{ dim_in }
		{
			size = new int[dim];
			for (int i = 0; i < dim; i++)
				size[i] = array_size[i];

			top = new Address;

			top->level = 0;

			initializeAddress(top);
		}

		Array(const Array &arr) :dim{ arr.dim }
		{
			size = new int[dim];
			for (int i = 0; i < dim; i++)
				size[i] = arr.size[i];

			top = new Address;
			top->level = 0;

			initializeAddress(top);

		}

		~Array()
		{
			deleteAddress(top);
			delete top;
			delete[] size;
		}

		Int operator[](const int index);

		//to copy the data of the array, use copyAddress recursive function.
		void copyAddress(Address *dst, Address *src)
		{
			if (dst->level == dim - 1)     // if level is dim-1, that means its next pointer is a pointer to int data type array.
			{
				for (int i = 0; i < size[dim - 1]; i++)
					static_cast<int *>(dst->next)[i] = static_cast<int *>(src->next)[i];

				return;
			}

			for (int i = 0; i < size[dst->level]; i++)                    // if level is not dim-1, that means its next pointer is a pointer to next level pointer array.
			{
				Address *new_dst = static_cast<Address *>(dst->next) + i; //for store the pointer(address) to next level pointer.
				Address *new_src = static_cast<Address *>(src->next) + i;

				copyAddress(new_dst, new_src);
			}
		}

		void initializeAddress(Address *current)
		{
			if (!current) return;
			if (current->level == dim - 1)       //for n dimensional array, 0 is the top of array and dim-1 is the last array which has real data.
			{
				current->next = new int[size[current->level]];  //dynamic allocation for data
				return;
			}

			current->next = new Address[size[current->level]];  //dynamic allocation for next array.

			for (int i = 0; i != size[current->level]; i++)     //in current address, there are size[current->level]'s number of data.
			{
				(static_cast<Address *>(current->next) + i)->level = current->level + 1;  //change the level of current array

				initializeAddress(static_cast<Address *>(current->next) + i);
			}
		}

		void deleteAddress(Address *current)
		{
			if (!current) return;
			for (int i = 0; current->level < dim - 1 && i < size[current->level]; i++)
				deleteAddress(static_cast<Address *>(current->next) + i);

			if (current->level == dim - 1)
				delete[] static_cast<int *>(current->next);
			else
				delete[] static_cast<Address *>(current->next);
		}

		class Iterator
		{
		private:
			int *location;
			Array *arr;

		public:
			Iterator(Array *arr_in, int *location_in=nullptr)
				:arr{ arr_in }
			{
				location = new int[arr->dim];
				for (int i = 0; i != arr->dim; i++)
					location[i] = (location_in != nullptr ? location_in[i] : 0);
			}

			Iterator(const Iterator &itr)
				:arr{ itr.arr }
			{
				location = new int[arr->dim];
				for (int i = 0; i != arr->dim; i++) location[i] = itr.location[i];
			}

			Iterator &operator=(const Iterator &itr)
			{
				arr = itr.arr;

				location = new int[arr->dim];

				for (int i = 0; i < arr->dim; i++)
					location[i] = itr.location[i];

				return *this;
			}

			Iterator &operator++()
			{
				if (location[0] >= arr->size[0])
					return *this;

				bool carry = false;
				int i = arr->dim - 1;

				do
				{
					location[i]++;

					if (location[i] >= arr->size[i] && i >= 1)    //do not back to the begin (0,0,0,..,0) because iterator end in the next of the end of the array.
					{
						location[i] -= arr->size[i];
						carry = true;
						i--;
					}

					else
						carry = false;

				} while (i >= 0 && carry);

				return *this;
			}

			Iterator &operator++(int)
			{
				Iterator temp(*this);

				++(*this);
				return temp;
			}

			bool operator!=(const Iterator &itr)
			{
				if (arr->dim != itr.arr->dim) return true;

				for (int i = 0; i < arr->dim; i++)
					if (location[i] != itr.location[i]) return true;

				return false;
			}

			Int operator*();
		};

		Iterator begin()
		{
			int *arr = new int[dim];
			for (int i = 0; i != dim; i++) arr[i] = 0;

			Iterator temp(this, arr);
			delete[] arr;

			return temp;
		}

		Iterator end()
		{
			int *arr = new int[dim];
			arr[0] = size[0];
			for (int i = 1; i < dim; i++) arr[i] = 0;

			Iterator temp(this, arr);
			delete[] arr;

			return temp;
		}
	};

	class Int
	{
	private:
		void  *data;

		int    level;
		Array *arr;

	public:
		Int(int index, int level_in=0, void* data_in = nullptr, Array *arr_in =nullptr)
			:level{level_in}, data{data_in}, arr{arr_in}
		{
			if (level < 1 || index >= arr->size[level_in - 1])     //여기서 level_in은 해당 배열을 담은 배열에 대한 레벨이 아니라 현재 []되고 있는 차원의 레벨을 의미 (가장 상위에 있는 레벨인 top이 0부터 시작하기 때문에 arr[][][]에서 arr[]은 레벨 1이고, arr[][]은 레벨 2이고, arr[][][]은 레벨 3이다.
			{
				data = nullptr;
				return;
			}

			if (level == arr->dim)
				data = static_cast<void *>(static_cast<int *>(static_cast<Array::Address *>(data)->next) + index);            //if level == dim(which means it's pointing to the data level.), data is a pointer that is pointing to the int data.

			else
				data = static_cast<void *>(static_cast<Array::Address *>(static_cast<Array::Address *>(data)->next) + index);  //if level is not dim, it has to store next level address to go down to the next level.
		}

		Int(const Int &i) : data{ i.data }, level{ i.level }, arr{ i.arr } {}      //for return by value. copy constructor.

		operator int()
		{
			if (data) return *static_cast<int *>(data);      //가장 마지막 레벨에 와서 암시적 형변환을 시도할 때, (int)Int의 data에 담긴 주소가 index에 의해 결정된 특정한 요소의 주소이므로, 이 주소를 int 타입 포인터로 변환하고, 이를 역참조하여 값을 얻음.
			return 0;
		}
		
		Int &operator=(const int &a)
		{
			if (data) *static_cast<int *>(data) = a;
			return *this;
		}

		Int operator[](const int index)
		{
			if (!data) return 0;
			return Int{ index,level + 1,data,arr };
		}
	};

	Int Array::operator[](const int index)
	{
		return Int{ index, 1, static_cast<void *>(top),this };
	}

	Int Array::Iterator::operator*()
	{
		Int start = arr->operator[](location[0]);
		for (int i = 1; i <= arr->dim - 1; i++)
			start = start.operator[](location[i]);

		return start;
	}
}



int main()
{

}
#include <iostream>
#include <string>

namespace Myarray
{
	class Array;
	class Int;

	class Array
	{
		friend Int;

	private:
		int  m_dimension;
		int *m_arr_size;

		struct Address
		{
			int   current_level;
			void *address_next_arr;
		};

		Address *top;

	public:
		class Iterator
		{
		private:
			int   *location;    //접근하고 있는 컨테이너 엘리먼트에 대한 정보를 담고 있는 배열
			Array *arr;         //돌고자 하는 컨테이너

		public:
			Iterator(Array *arr_in, int *location_in = nullptr) : arr{ arr_in }
			{
				location = new int[arr->m_dimension];
				for (int i = 0; i != arr->m_dimension; i++)
					location[i] = (location_in != nullptr ? location_in[i] : 0);
			}

			Iterator(const Iterator &itr) :arr{ itr.arr }
			{
				location = new int[arr->m_dimension];
				for (int i = 0; i != arr->m_dimension; i++)
					location[i] = itr.location[i];
			}

			~Iterator() { delete[] location; }

			//시작부터 끝까지 하니씩 도는 장치를 만들기 위해 ++를 정의

			Iterator &operator++()
			{
				if (location[0] >= arr->m_arr_size[0]) return *this;

				bool carry = false;
				int i = arr->m_dimension - 1;      //3차원 배열이면 location은 location[2]까지 존재

				do
				{
					location[i]++;

					if (location[i] >= arr->m_arr_size[i] && i >= 1)         //마지막 배열에서 location[0]이 arr->m_size_arr[0]보다 커져서 if문 안으로 들어가게 되면 location의 원소가 00000으로 바뀌면서 시작점과 같아지는 모순을 피하기 위해 i>=1 일때만 if문 안으로 들어가서 carry를 true로
					{
						location[i] -= arr->m_arr_size[i];
						carry = true;
						i--;
					}

					else
						carry = false;
		
				} while (carry && i >= 0);          //i가 0이여도 carry가 true면 location[i]를 1 증가시켜야 한다. 만약 location[i]가 arr->m_arr_size[i]보다 작아서 carry가 false라면 빠져나와서 *this를 리턴
				
				return *this;
			}

			Iterator& operator++(int)
			{
				Iterator itr{ *this };
				++(*this);

				return itr;
			}

			Int operator*();

			bool operator!=(const Iterator &itr)
			{
				if (arr->m_dimension != itr.arr->m_dimension)
					return true;

				for (int i = 0; i < arr->m_dimension; i++)
					if (location[i] != itr.location[i])
						return true;

				return false;
			}

			Iterator &operator=(const Iterator &itr)
			{
				arr = itr.arr;
				location = new int[arr->m_dimension];

				for (int i = 0; i < arr->m_dimension; i++)
					location[i] = itr.location[i];

				return *this;
			}
		};


		Array(int dimension_in, int *arr_size_in)
			:m_dimension{ dimension_in }
		{
			m_arr_size = new int[m_dimension];

			for (int i = 0; i < m_dimension; i++)
				m_arr_size[i] = arr_size_in[i];

			top = new Address;
			top->current_level = 0;

			initializeAddress(top);
		}

		Array(const Array &arr) : m_dimension{ arr.m_dimension }
		{
			m_arr_size = new int[m_dimension];

			for (int i = 0; i < m_dimension; i++)
				m_arr_size[i] = arr.m_arr_size[i];

			top = new Address;
			top->current_level = 0;

			initializeAddress(top);

		}

		~Array()
		{
			deleteAddress(top);
			delete top;
			delete[] m_arr_size;
		}

		Int operator[](const int index);

		void deleteAddress(Address *current)
		{
			if (!current) return;
			for (int i = 0; (current->current_level < m_dimension - 1) && i < m_arr_size[current->current_level]; i++)
				deleteAddress(static_cast<Address *>(current->address_next_arr) + i);

			if (current->current_level == m_dimension - 1)
				delete[] static_cast<int *>(current->address_next_arr);

			delete[] static_cast<Address *>(current->address_next_arr);
		}

		void initializeAddress(Address *current)
		{
			if (!current) return;

			else if (current->current_level == m_dimension - 1)
			{
				current->address_next_arr = new int[m_arr_size[current->current_level]];
				return;
			}

			else
			{
				current->address_next_arr = new Address[current->current_level];

				for (int i = 0; i < current->current_level; i++)
				{
					(static_cast<Address *>(current->address_next_arr) + i)->current_level = current->current_level + 1;

					initializeAddress(static_cast<Address *>(current->address_next_arr) + i);
				}
			}
		}

		void copyAddress(const Address *dst, const Address *src)
		{
			if (dst->current_level == m_dimension - 1)
			{
				for (int i = 0; i < m_arr_size[dst->current_level]; i++)
					static_cast<int *>(dst->address_next_arr)[i] = static_cast<int *>(src->address_next_arr)[i];

				return;
			}

			else
				for (int i = 0; i < m_arr_size[dst->current_level]; i++)
				{
					Address *new_dst = static_cast<Address *>(dst->address_next_arr) + i;
					Address *new_src = static_cast<Address *>(src->address_next_arr) + i;

					copyAddress(new_dst, new_src);
				}
		}

		Iterator begin()
		{
			int *arr = new int[m_dimension];

			for (int i = 0; i < m_dimension; i++)
				arr[i] = 0;

			Iterator temp(this, arr);

			delete[] arr;

			return temp;
		}

		Iterator end()
		{
			int *arr = new int[m_dimension];

			arr[0] = m_arr_size[0];

			for (int i = 1; i < m_dimension; i++)
				arr[i] = 0;

			Iterator temp(this, arr);

			delete[] arr;

			return temp;
		}
	};

	class Int
	{
	private:
		void *data;    //참조할 배열의 주소값(address 클래스)을 가지고 있음.

		int level;     //data에 담긴 주소가 어느 레벨에 해당하는지를 표시
		Array *array;  //참조하는 배열을 표시

	public:
		Int(int index, int level_in = 0, void *data_in = nullptr, Array *array_in = nullptr)
			:level{ level_in }, data{ data_in }, array{ array_in }
		{
			//dereferencing 하는 레벨이 1보다 크지 않거나(arr[1]은 arr[1]에 담긴 값을 리턴해야 되기 때문에 level 0은 리턴할 값이 없다.), 인덱스가 해당 레벨의 배열의 요소 수보다 클 경우에는 null값 리턴
			if (level_in < 1 || index >= array->m_arr_size[level_in - 1])
			{
				data = nullptr;
				return;
			}

			//int를 배열로 가지고 있는 레벨까지 도달 했을 경우에
			if (level == array->m_dimension)
				data = static_cast<void *>(static_cast<int *>(static_cast<Array::Address *>(data)->address_next_arr) + index);

			else
				data = static_cast<void *>(static_cast<Array::Address *>(static_cast<Array::Address *>(data)->address_next_arr) + index);
		}

		Int(const Int &i):level{i.level}, data{i.data}, array{i.array}{}

		//최종적으로 동적할당 된 int 배열의 보이드 포인터가 반환되면 그것을 암시적 형 변환으로 int를 리턴하는 operator
		operator int()
		{
			if (data) return *static_cast<int *>(data);

			else
				return 0;
		}

		Int &operator=(const int &a)
		{
			if (data) *static_cast<int *>(data) = a;
			return *this;
		}

		//arr[index]로 리턴되는 값은 전적으로 Int constructor에 의해 다음 레벨을 지칭하는 data를 넣어주면서 진행
		Int operator[](const int index)
		{
			if (!data) return 0;
			else
				return Int(index, level + 1, data, array);
		}
	};

	//다음 레벨의 Int를 리턴하기 위하여 현재 Array클래스가 가지고 있는 배열의 레벨 0 주소를 넣어주면, Int constructor에서 다음 레벨의 data를 가지는 Int를 생성하는 형식으로 진행.
	Int Array::operator[](const int index)
	{
		return Int(index, 1, static_cast<void*>(top), this);
	}

	Int Array::Iterator::operator*()
	{
		Int start = arr->operator[](location[0]);

		for (int i = 1; i < arr->m_dimension; i++)
			start = start.operator[](location[i]);

		return start;
	}
}

int main()
{}
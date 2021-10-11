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
			int   *location;    //�����ϰ� �ִ� �����̳� ������Ʈ�� ���� ������ ��� �ִ� �迭
			Array *arr;         //������ �ϴ� �����̳�

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

			//���ۺ��� ������ �ϴϾ� ���� ��ġ�� ����� ���� ++�� ����

			Iterator &operator++()
			{
				if (location[0] >= arr->m_arr_size[0]) return *this;

				bool carry = false;
				int i = arr->m_dimension - 1;      //3���� �迭�̸� location�� location[2]���� ����

				do
				{
					location[i]++;

					if (location[i] >= arr->m_arr_size[i] && i >= 1)         //������ �迭���� location[0]�� arr->m_size_arr[0]���� Ŀ���� if�� ������ ���� �Ǹ� location�� ���Ұ� 00000���� �ٲ�鼭 �������� �������� ����� ���ϱ� ���� i>=1 �϶��� if�� ������ ���� carry�� true��
					{
						location[i] -= arr->m_arr_size[i];
						carry = true;
						i--;
					}

					else
						carry = false;
		
				} while (carry && i >= 0);          //i�� 0�̿��� carry�� true�� location[i]�� 1 �������Ѿ� �Ѵ�. ���� location[i]�� arr->m_arr_size[i]���� �۾Ƽ� carry�� false��� �������ͼ� *this�� ����
				
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
		void *data;    //������ �迭�� �ּҰ�(address Ŭ����)�� ������ ����.

		int level;     //data�� ��� �ּҰ� ��� ������ �ش��ϴ����� ǥ��
		Array *array;  //�����ϴ� �迭�� ǥ��

	public:
		Int(int index, int level_in = 0, void *data_in = nullptr, Array *array_in = nullptr)
			:level{ level_in }, data{ data_in }, array{ array_in }
		{
			//dereferencing �ϴ� ������ 1���� ũ�� �ʰų�(arr[1]�� arr[1]�� ��� ���� �����ؾ� �Ǳ� ������ level 0�� ������ ���� ����.), �ε����� �ش� ������ �迭�� ��� ������ Ŭ ��쿡�� null�� ����
			if (level_in < 1 || index >= array->m_arr_size[level_in - 1])
			{
				data = nullptr;
				return;
			}

			//int�� �迭�� ������ �ִ� �������� ���� ���� ��쿡
			if (level == array->m_dimension)
				data = static_cast<void *>(static_cast<int *>(static_cast<Array::Address *>(data)->address_next_arr) + index);

			else
				data = static_cast<void *>(static_cast<Array::Address *>(static_cast<Array::Address *>(data)->address_next_arr) + index);
		}

		Int(const Int &i):level{i.level}, data{i.data}, array{i.array}{}

		//���������� �����Ҵ� �� int �迭�� ���̵� �����Ͱ� ��ȯ�Ǹ� �װ��� �Ͻ��� �� ��ȯ���� int�� �����ϴ� operator
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

		//arr[index]�� ���ϵǴ� ���� �������� Int constructor�� ���� ���� ������ ��Ī�ϴ� data�� �־��ָ鼭 ����
		Int operator[](const int index)
		{
			if (!data) return 0;
			else
				return Int(index, level + 1, data, array);
		}
	};

	//���� ������ Int�� �����ϱ� ���Ͽ� ���� ArrayŬ������ ������ �ִ� �迭�� ���� 0 �ּҸ� �־��ָ�, Int constructor���� ���� ������ data�� ������ Int�� �����ϴ� �������� ����.
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
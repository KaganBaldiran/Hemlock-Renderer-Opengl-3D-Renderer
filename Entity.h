#ifndef ENTITY 
#define ENTITY 

#include <iostream>
#include <vector>
#include "Light.h"
#include "Model.h"

#define LIGHTTYPE "class Light"
#define MODELTYPE "class Model"
#define SUCCESS 1
#define FAIL -1

typedef unsigned long int Entity_id_t;
typedef std::string Entity_type_t;
typedef unsigned int Entity_stencil_index;
typedef short int Entity_Flag_t

class Entity
{
public:


	Entity() 
	{
		this->ID = GenerateEntityID();
		this->entitytype = {};
		this->data = nullptr;
	};

	Entity(Entity_type_t entitytype_p , const char* filepath) :entitytype(entitytype_p), data(nullptr)
	{
		this->ID = GenerateEntityID();
		data = new Model(filepath);
		data_allocated = true;
		
	}

	Entity(Entity_type_t entitytype_p ,void *data) :entitytype(entitytype_p) 
	{
		this->ID = GenerateEntityID();

		this->data = (void*)data;

	}
	
	template<typename typenme>
	typenme* CreateEntityWithSubPrimitive(Entity_type_t entitytype_p , const char* filepath)
	{
	     this->data = new Model(filepath);
	     this->data_allocated = true;	
	  
	     return (typenme*)this->data;
	}
	
	Entity_Flag_t DeleteSubPrimitive()
	{
	     delete data;
		
	     if(data)
	     {
		return SUCCESS; 
	     }
	     else
	     {
		return FAIL;     
	     }
		
	}
    
	template<typename typenm>
	typenm* GetData() 
	{
		
		try
		{
			if (typeid(typenm).name() == entitytype)
			{
				return (typenm*)this->data;
			}
			else
			{
				throw std::runtime_error("Given entity type is not the same with the initialized type");
			}

		}
		catch (runtime_error error)
		{
			std::cout << "Entity :: Runtime error: " << error.what() << "\n";
			exit(-1);
		}

	};
	
	void AddComponent(void* component)
	{
	    componenents.push_back(component);	
	}
	
	template<typename type1, typename type2 , typename output_type>
	output_type SetComponents((*fun)(type1 , type2))
	{
	    return (*fun)(int , int);
	}
	
	~Entity()
	{
		if (data_allocated)
		{
		    delete data;
		}
	}


private:

	Entity_id_t ID;
	Entity_type_t entitytype;
	Entity_stencil_index stencil_index;

	void* data;
	bool data_allocated = false;
	
	std::vector<void*> components;
	
	Entity_id_t GenerateEntityID()
	{
		static Entity_id_t increment = NULL;

		increment++;

		return increment;
	}


};


#endif // !ENTITY


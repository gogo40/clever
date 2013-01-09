#include "core/value.h"
#include "types/array.h"

namespace clever {

void* ArrayType::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	ArrayObject* arr = new ArrayObject();
	std::vector<Value*>& vec = arr->getData();

	for (size_t i = 0, j = args->size(); i < j; ++i) {
		Value* val = new Value();

		val->copy(args->at(i));

		vec.push_back(val);
	}

	return arr;
}

void ArrayType::deallocData(void* data)
{
	ArrayObject* arr = static_cast<ArrayObject*>(data);
	std::vector<Value*>& vec = arr->getData();

	for (size_t i = 0, j = vec.size(); i < j; ++i) {
		vec[i]->delRef();
	}

	delete arr;
}

void ArrayType::dump(const void* value, std::ostream& out) const
{
	Value::DataValue* data = static_cast<Value::DataValue*>(const_cast<void*>(value));
	ArrayObject* arr = static_cast<ArrayObject*>(data->obj->getObj());
	std::vector<Value*>& vec = arr->getData();

	out << "[";

	for (size_t i = 0, j = vec.size(); i < j; ++i) {
		vec.at(i)->dump(out);
		if (i < j-1) {
			out << ", ";
		}
	}

	out << "]";
}

CLEVER_METHOD(ArrayType::append)
{
	ArrayObject* arr = CLEVER_GET_OBJECT(ArrayObject*, CLEVER_THIS());

	for (size_t i = 0, j = CLEVER_ARG_COUNT(); i < j; ++i) {
		arr->getData().push_back(args[i]);
		args[i]->addRef();
	}
}

CLEVER_TYPE_INIT(ArrayType::init)
{
	addMethod(CSTRING("append"), (MethodPtr) &ArrayType::append);
}

} // clever

#include "Element.h"

Element::Element(const string _sign) {
	sign = _sign;
}

ostream& operator << (ostream& _stream, Element* _element) {
	return _stream << _element->GetSign();
}
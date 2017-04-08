# C++

### Rzutowanie

Jak sprawdzić czy zmienna `node` jest typu `ProcedureNode`:

```c++
ProcedureNode* procedureNode = dynamic_cast<ProcedureNode*>(node);
```

Jeśli rzutowanie przebiegnie poprawnie, to `prodecureNode` bedzie wskazywało na obiekt, a jeśli nie, to `procedureNode` będzie miało wartość `nullptr`.
Ponadto rzutowanie działa w dwie strony (chyba), czyli:

 * Node -> ProcedureNode
 * ProcedureNode -> Node

## Testy

### Jak sprawdzić, czy metoda wyrzuca wyjątek?

Mamy taką metodę, która dodaje dziecko do tablicy. Jeśli dziecko nie jest typu `ProcedureNode`, to wyrzuca wyjątek typu `invalid_argument`.

```c++
void ProgramNode::addChild(Node* child) {
	if(dynamic_cast<ProcedureNode*>(child) == nullptr) {
		throw invalid_argument("ProgramNode accepts only ProcedureNode as a child);
	}

	this->children.push_back(child);
}
```

Teraz w testowej klasie `ProgramNodeTest` w projekcie `UnitTesting` robie takie coś:
```c++
#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/ProgramNode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(FOO) {//nazwa dowolna
	TEST_METHOD(addProperChildType) {//nazwa dowolna
		ProgramNode* programNode = new ProgramNode;//tworze nowy testowy programNode
		
		/*
    		Tutaj tworze sobie taką dziwną funkcję.
    		W jej ciele wywołuje metodę, która ma wyrzucić wyjątek, a jako parametr w nawiasach '[]' podaję obiekt, z którego wywoływana będzie metoda.
    		Słowo kluczowe 'auto' określa, że zmienna będzie dowolnego typu.
		*/
		auto pointer = [programNode] { 
			programNode->addChild(programNode); 
		};

    /*
        Tutaj sprawdzam, czy ciało naszej dziwnej funkcji wyrzuciło jakiś wyjątek.
        W nawiasach '<>' podaję typ naszego wyjątku (wyrzuciliśmy 'throw invalid_argument("..."))
    */
		Assert::ExpectException<invalid_argument>(pointer);
		
		delete programNode; //na końcu usuwam obiekt.
	}
};
```

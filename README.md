# C++

### Rzutowanie

Jak sprawdzić czy zmienna `node` jest typu `ProcedureNode`:
```c++
ProcedureNode* procedureNode = dynamic_cast<ProcedureNode*>(node);
```

Jeśli zrzutuje poprawnie, to `prodecureNode` bedzie wskazywało na obiekt, a jeśli nie, to `procedureNode` będzie `nullptr`.

Rzutowanie działa w dwie strony (chyba), czyli:

Node -> ProcedureNode

ProcedureNode -> Node

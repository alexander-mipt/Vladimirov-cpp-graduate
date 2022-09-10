# RAII & moving constructor
## `goto` (Deikstra 1976)
`goto` can be used to free resources:
```
if (cond) {
	result = FAIL;
	goto cleanup;
}

cleanup:
	delete p;
	return result;
```
Do not use `goto` because it makes from вложенного дерева произвольный граф, что не очень хорошо.

```
break, countinue, switch - similar
```

**Дуги не должны пропускать создание объектов (время жизни)**


## `operator->()` overload (drill down behaviour)
```
T* operator->() { return x; } // p->x <==> (p.operator->())->x
```

Перестановка указателей местами без семантики перемещения работает крайне неэффективно.

доделать про перемещающие конструкторы

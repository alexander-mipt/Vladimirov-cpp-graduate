# Lecture 20

`std::exchange`

 `std::find_if_not`

## ADL (argument depended lookup)

если функция не может быть найдена в текущем namespace и в охватывающих - она будет искаться в namespace аргументов.

![image-20221216112634432](media/image-20221216112634432.png)

![image-20221216112645824](media/image-20221216112645824.png)

![image-20221216112706309](media/image-20221216112706309.png)

![image-20221216112724884](media/image-20221216112724884.png)

![image-20221216112737090](media/image-20221216112737090.png)

![image-20221216112748582](media/image-20221216112748582.png)

**Итератор - копируемый объект!**

![image-20221216113520933](media/image-20221216113520933.png)

![image-20221216113559931](media/image-20221216113559931.png)

Если не лезть в контейнер, то из-за -1 уровня косвенности будет ускорение по производительности:

![image-20221216113705187](media/image-20221216113705187.png)

У итераторов синтаксически одинаковый интерфейс, за исключением класса характеристик:

![image-20221216114206389](media/image-20221216114206389.png)

Их можно вывести, перегрузив оператор <<

![image-20221216114732691](media/image-20221216114732691.png)

random

forward

bidirect

random

input

output

![image-20221216132200733](media/image-20221216132200733.png)

Как вывести reverse range based?

![image-20221216132610348](media/image-20221216132610348.png)

## Adapters

* inserters (back / front)
* 
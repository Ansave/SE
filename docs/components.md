# Компонентная архитектура
## Компонентная диаграмма
```plantuml
@startuml
!include https://raw.githubusercontent.com/plantuml-stdlib/C4-PlantUML/master/C4_Container.puml

AddElementTag("microService", $shape=EightSidedShape(), $bgColor="CornflowerBlue", $fontColor="white", $legendText="microservice")
AddElementTag("storage", $shape=RoundedBoxShape(), $bgColor="lightSkyBlue", $fontColor="white")

Person(user, "Пользователь")
Person(commodity_manager, "Менеджер продуктов")

System_Boundary(store_site, "Сайт магазина") {
    Container(store_front, "Лицевая сторона сайта", "C++/HTML", "Отображаемое пользователю лицо сайта, взаимодествует с микросервисами", $tags = "microService")
    Container(auth_service, "Сервис авторизации", "C++", "Сервис управления пользователями", $tags = "microService")
    Container(commodity_service, "Сервис товаров", "C++", "Предоставляет все доступные товары и информацию о них", $tags = "microService")
    Container(cart_service, "Сервис корзины", "C++", "Сервис для хранения и выдачи информации о корзине пользователя", $tags = "microService")

    ContainerDb(user_db, "База данных пользователей", "MySQL", "Хранит данные о пользователе", $tags = "storage")
    ContainerDb(commodity_db, "База данных продуктов", "MySQL", "Хранит данные о продуктах", $tags = "storage")
    ContainerDb(cart_db, "База данных корзин", "MySQL", "Хранит данные о продуктах", $tags = "storage")
}

Rel(user, store_front, "Взаимодействует с сайтом: регистрируется, просматривает продукты, создает заказы")
Rel(commodity_manager, store_front, "Добавляет новые товары и редактирует цены/количество существующих")

Rel(store_front, auth_service, "Проверяет введенные пользователем данные, ищет по логину или маске имени и фамилии", "API")
Rel(store_front, commodity_service, "Получает список товаров, создает новый или редактирует существующий", "API")
Rel(store_front, cart_service, "Добавляет товар в корзину и показывает её содержимое", "API")

Rel(cart_service, commodity_service, "Проверяет существование товара", "API")

Rel(auth_service, user_db, "CRUD операция", "SQL")
Rel(commodity_service, commodity_db, "CRUD операция", "SQL")
Rel(cart_service, cart_db, "CRUD операция", "SQL")

@enduml
```

## Список компонентов

### Сервис авторизации
**API**:
* Создание нового пользователя
    * входные параметры: login, пароль, имя, фамилия, email, пол
    * выходные параметры: отсутствуют
* Авторизация
    * входные параметры: login, пароль
    * выходные параметры: cookie сессии
* Поиск пользователя по логину
    * входные параметры:  login
    * выходные параметры: имя, фамилия, email, пол
* Поиск пользователя по маске имени и фамилии
    * входные параметры: маска фамилии, маска имени
    * выходные параметры: login, имя, фамилия, email, пол

### Сервис товаров
**API**:
* Создание нового товара
    * входные параметры: Название, количество, цена
    * выходные параметры: id товара
* Получение списка товаров
    * входные параметры:  нет
    * выходные параметры: Список из товаров (словарей из id товара, названия, количества, цены)
* Получение информации о товаре
    * входные параметры:  id
    * выходные параметры: название товара, количество, цена

### Сервис корзины
**API**:
* Добавление товара в корзину
    * входные параметры:  id товара, id пользователя
    * выходные параметры: статус
* Получение содержимого корзины для пользователя
    * входные параметры:  id пользователя
    * выходные параметры: список из id товаров

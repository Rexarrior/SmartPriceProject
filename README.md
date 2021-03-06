# SmartPriceProject
# Проект "Умные ценники". 

Выполняется студентами ПМПУ СПБГУ для IoT Академии Samsung в 2020 году. 
### Состав проектной команды:
* Родионов Александр
* Киреев Сергей 

### Презентация проекта
* [ИОТ Умные Ценники](https://docs.google.com/presentation/d/1CsZbk4YONBEhG9cXoQ8nCgpMzJ0dXboU5oR-GBdHOWk/edit#slide=id.p "")


### Архитектура проекта следующая:
* Сервер системы умных ценников. 
* База данных системы умных ценников. Связана с базой данных организации-магазина. 
* Станции-полки - устройства, призванные управлять массивом умных ценников, соответствующих одной полке. Выполняются в двух вариантах - автономные и с постоянным питанием от эллектрической сети. Осуществвляют связь с сервером системы посредством интерфейса беспроводной связи. 
* Умные ценники - E-inc экраны, отображающие актуальную (согласно базе данных магазина) цену на товар, за которым закреплены. Располагаются на общей шине, ведущей к станции. Управляются по интерфейсу spi. 
* Сканер штрих кода. Вспомогательное устройство, предназначенное для упрощения настройки ценника на товар. Настройка осуществляется по следующему алгоритму: выполняется скнирование штрих-кода ценника, выполняется сканирование штрих-кода товара. Информация отсылается на сервер, сервер производит сопоставление в базе и передает на станцию, соответствующую настраиваемому ценнику, информацию о новом товаре и цене на него. 


### На текущей стади Проект выполняется в формате прототипа. Прототип включает в себя следующее:
* Сервер системы умных ценников с минимальным функционалом
* База данных системы умных ценников с интегрированной в нее минимальной базой о товарах магазина
* Прототип станции с подключенным к ней одним умным ценником. Включает в себя следующие аппаратные элементы:
    * [stm32l152RCT6-Discovery](https://www.st.com/en/evaluation-tools/32l152cdiscovery.html "") в качестве контроллера и основной платы станции
    * e-inc дисплей [DEW0213T5](http://www.e-paper-display.com/products_detail/productId=309.html "") от компании GoodDisplay в качестве умного ценника
    * адаптер дисплея [DESPI-CO2](http://www.e-paper-display.com/products_detail/productId=403.html "")
    * Li-ion аккумулятор в качестве автономного источника питания
    * [ESP01](https://www.chipdip.ru/product/esp-01 "") в качестве интерфейса беспроводной связи (wifi)

    

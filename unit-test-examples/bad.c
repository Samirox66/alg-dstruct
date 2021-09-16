/*
Ошибка - название не отражает суть теста.
Ошибка - функция Pop начинает свою работу со списком, созданным и пополненым
    функцией Push. В таком случае нельзя гарантировать, что список находится в том состоянии,
    которое вы желаете. Для проверки функции Pop, список надо инициализировать вручную.
Ошибка - неочевидное использование чисел. Если число не принципиально, используем самые интуитивные, т.е. 1, 2, 3 и т.д.
    Если "сложное" число необходимо - выносим в отдельную переменную с говорящим названием.
*/
TEST(StackListTest, Test_Pop) {
    stackList_t* head;
    PushList(&head, 12563);
    PushList(&head, 553);
    ASSERT_EQ(553, PopList(&head));
    ASSERT_EQ(12563, head->value);
}

/*
Ошибка - тест невоспроизводим. Используется случайное число.
*/
TEST(StackListTest, PeekListTest_return30) {
    stackList_t* head;
    time_t now = time(0)
    PushList(&head, now);
    ASSERT_EQ(now, PeekList(head));
}

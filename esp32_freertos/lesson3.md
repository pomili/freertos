# System Startup Flow
1. First stage bootloader(ROM)
2. Second stage bootloader()
3. Application Startup

app_main->main_task

main_task 是创建的一个任务，使用函数xTaskCreatePinnedToCore(&mian_task,"main",..,ESP_TASK_MIAN_CORE);

mian_task->

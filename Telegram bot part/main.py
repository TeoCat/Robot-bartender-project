import logging
from aiogram import Bot, Dispatcher, executor
from config import BOT_TOKEN

bot = Bot(BOT_TOKEN,  parse_mode="HTML")
dp = Dispatcher(bot)

logging.basicConfig(format=u'%(filename)s [LINE:%(lineno)d] #%(levelname)-8s [%(asctime)s]  %(message)s',
                    level=logging.INFO,
                    )

if __name__ == '__main__':
    from handlers import dp, send_to_admin

    executor.start_polling(dp, on_startup=send_to_admin)

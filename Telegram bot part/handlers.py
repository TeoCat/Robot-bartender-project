from main import bot, dp
import logging
from aiogram.dispatcher.filters import Command, Text
from aiogram.types import Message, CallbackQuery
from config import id_admin
from keyboard import menu, categories, id_jin, id_vodka
import requests
from requests.exceptions import ConnectionError
from CallBack import callback
import websockets


async def send_to_admin(ip=0, id=0, number=0):
    if id == 0 & number == 0:
        await bot.send_message(chat_id=id_admin, text="Бот запущен")
    else:
        async with websockets.connect('ws://******/ws') as websocket:
            response = await websocket.recv()
            print(response)
            await websocket.send(f"{id}, {number}")


@dp.message_handler(Command("menu"))
async def show_menu(message: Message):
    await message.answer("Выберите функции", reply_markup=menu)


@dp.message_handler(Text(equals=["Меню коктейлей"]))
async def get_menu(message: Message):
    # Часть в разработке
    if message.text == "Включить":
        try:
            response = requests.get('http://192.168.0.100/')
            print(response.status_code)
        except ConnectionError:
            print('Ошибка соединения')
        await message.answer("Вы выбрали ...")
    # единственный пункт
    elif message.text == "Меню коктейлей":
        await message.answer(text="Выберете основу", reply_markup=categories)


@dp.callback_query_handler(callback.filter(categories="Vodka", id="0"))
async def alcohol_selection1(call: CallbackQuery):
    await call.answer(cache_time=1)
    await call.message.edit_reply_markup(id_vodka)


@dp.callback_query_handler(callback.filter(categories="Jin", id="0"))
async def alcohol_selection2(call: CallbackQuery):
    await call.answer(cache_time=1)
    await call.message.edit_reply_markup(id_jin)


@dp.callback_query_handler(callback.filter(categories="Vodka", id="Otvertka"))
async def callback_otvertka(call: CallbackQuery, callback_data: dict):
    await call.answer(cache_time=1)
    logging.info(f"{callback_data=}")
    id_drink = callback_data.get("id")
    number = call.from_user
    await call.message.answer(f"Вы выбрали коктель {id_drink}, спасибо")
    await send_to_admin(id=id_drink, number=int(number))
    await call.message.edit_reply_markup(reply_markup=None)


@dp.callback_query_handler(callback.filter(categories="Jin", id="Jin_tonic"))
async def callback_jin_tonic(call: CallbackQuery, callback_data: dict):
    await call.answer(cache_time=1)
    logging.info(f"{callback_data=}")
    id_drink = callback_data.get("id")
    number = call.from_user
    await call.message.answer(f"Вы выбрали коктель {id_drink}, спасибо")
    await send_to_admin(id=id_drink, number=int(number))
    await call.message.edit_reply_markup(reply_markup=None)


@dp.callback_query_handler(text="back")
async def callback_back(call: CallbackQuery):
    await call.answer(cache_time=1)
    await call.message.edit_reply_markup(categories)


@dp.callback_query_handler(text="reset")
async def callback_reset(call: CallbackQuery):
    await call.answer("You cancel menu", show_alert=True)
    await call.message.edit_reply_markup(reply_markup=None)

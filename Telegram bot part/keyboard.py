from aiogram.types import ReplyKeyboardMarkup, KeyboardButton, InlineKeyboardButton, InlineKeyboardMarkup

from CallBack import callback

menu = ReplyKeyboardMarkup(
    keyboard=[
        [
            KeyboardButton(text="Меню коктейлей")
        ]
    ],
    resize_keyboard=True
)

categories = InlineKeyboardMarkup(row_width=2, inline_keyboard=[
    [
        InlineKeyboardButton(text="С водкой", callback_data=callback.new(categories="Vodka",
                                                                         id="0")),
        InlineKeyboardButton(text="С джином", callback_data="drinks:Jin:0")
    ],
    [
        InlineKeyboardButton(text="Отмена", callback_data="reset")
    ]
])

id_vodka = InlineKeyboardMarkup(row_width=1, inline_keyboard=[
    [
        InlineKeyboardButton(text="Отвертка", callback_data="drinks:Vodka:Otvertka")
    ],
    [
        InlineKeyboardButton(text="Назад", callback_data="back")
    ]
])

id_jin = InlineKeyboardMarkup(row_width=1, inline_keyboard=[
    [
        InlineKeyboardButton(text="Джин тоник", callback_data="drinks:Jin:Jin_tonic")
    ],
    [
        InlineKeyboardButton(text="Назад", callback_data="back")
    ]
])

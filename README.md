# PACMAN Version 2.0

## Headers

# Giới thiệu chung
**Pacman Version 2.0** là trò chơi Pacman cổ điển  kết hợp cùng BombIT. Trong game, Pacman sẽ cố gắng tích càng nhiều điểm và ăn hết xu để qua màn mà không gặp phải bất kì con ma nào. Trong version này, Pacman đã được trang bị thêm vũ khí Bom Laser để tiêu diệt ma một cách dễ dàng hơn.

# 1. Cách cài đặt game
### Unordered
* Tải Visual Studio Code tùy theo máy tính của bạn (https://code.visualstudio.com/download).
* Clone repo này về bằng lệnh "git clone link .git của repo" hoặc Chọn Code -> Download Zip. Giải nén code ra 1 Folder
* Cài đặt thư viện SDL 2.0: Vì trong repo của mình đã có sẵn các thư viện nên các bạn sẽ không cần thiết phải cài lại các thư viện kia nữa. Thay vào đó, hãy truy cập [Link này](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php) và làm theo từ bước 8 nhé.
* Bật Visual Studio Code lên và mở folder đã giải nén ra.
* Nháy chuột vào Terminal và gõ dòng lệnh make

# 2.Bắt đầu game

## 2.1Sau khi đã biên dịch xong thì Menu của game sẽ hiện ra như này:

![Pacman Pause Menu](https://github.com/vovanhai2005/Pacman_V2/assets/142618703/6a3a4730-98fe-46d1-9d89-65d1a8119c01)

Menu sẽ bao gồm các tính năng:
* **New Game**: bắt đầu một game mới
* **How To Play**: hướng dẫn cách chơi
* **Highscore**: Xem bảng xếp hạng điểm
* **SOUND: ON/OFF**: Bật/Tắt âm thanh game
* **Quit**: Thoát game

## 2.2Khi vào game, người chơi sẽ được đưa đến màn hình chơi như sau:

![Game](https://github.com/vovanhai2005/Pacman_V2/assets/142618703/0ec8243a-bc23-4b5e-b4b7-16a4e3314310)

Nhiệm vụ của người chơi là di chuyển pacman và thu thập nhiều điểm nhất có thể

# 3. Nhân vật, kẻ địch và item của game
## 3.1 Nhân vật
* Pacman:  ![pacman](https://github.com/vovanhai2005/Pacman_V2/assets/142618703/3bae88ec-0e63-4dcf-93f3-c6d53637ea46)
## 3.2 Kẻ địch
* Blinky: ![Blinky](https://github.com/vovanhai2005/Pacman_V2/assets/142618703/331a8e52-7eea-4c54-97f3-7b5264d28772)
* Pinky: ![Pinky](https://github.com/vovanhai2005/Pacman_V2/assets/142618703/10cca7bb-9ad7-4fd2-bd42-a71eb78014f8)
* Inky: ![Inky](https://github.com/vovanhai2005/Pacman_V2/assets/142618703/7b2001b8-10d9-4042-8100-ea6cc3bda794)
* Clyde:
##









*This text will be italic*  
_This will also be italic_

**This text will be bold**  
__This will also be bold__

_You **can** combine them_

## Lists

### Unordered

* Item 1
* Item 2
* Item 2a
* Item 2b

### Ordered

1. Item 1
2. Item 2
3. Item 3
    1. Item 3a
    2. Item 3b

## Images

![This is an alt text.](/image/sample.webp "This is a sample image.")

## Links

You may be using [Markdown Live Preview](https://markdownlivepreview.com/).

## Blockquotes

> Markdown is a lightweight markup language with plain-text-formatting syntax, created in 2004 by John Gruber with Aaron Swartz.
>
>> Markdown is often used to format readme files, for writing messages in online discussion forums, and to create rich text using a plain text editor.

## Tables

| Left columns  | Right columns |
| ------------- |:-------------:|
| left foo      | right foo     |
| left bar      | right bar     |
| left baz      | right baz     |

## Blocks of code

```
let message = 'Hello world';
alert(message);
```

## Inline code

This web site is using `markedjs/marked`.

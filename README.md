# PACMAN Version 2.0

# Giới thiệu chung
**Pacman Version 2.0** là trò chơi Pacman cổ điển  kết hợp cùng BombIT. Trong game, Pacman sẽ cố gắng tích càng nhiều điểm và ăn hết xu để qua màn mà không gặp phải bất kì con ma nào. Trong version này, Pacman đã được trang bị thêm vũ khí Bom Laser để tiêu diệt ma một cách dễ dàng hơn.

Link demo video về game:

# 1. Cách cài đặt game
## Tải game và compile bằng code
* Tải Visual Studio Code tùy theo máy tính của bạn (https://code.visualstudio.com/download).
* Clone repo này về bằng lệnh "git clone link .git của repo" hoặc Chọn Code -> Download Zip. Giải nén code ra 1 Folder
* Cài đặt thư viện SDL 2.0: Vì trong repo của mình đã có sẵn các thư viện nên các bạn sẽ không cần thiết phải cài lại các thư viện kia nữa. Thay vào đó, hãy truy cập [Link này](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php) và làm theo từ bước 8 nhé.
* Bật Visual Studio Code lên và mở folder đã giải nén ra.
* Nháy chuột vào Terminal và gõ dòng lệnh make

# 2.Bắt đầu game

## 2.1 Sau khi đã biên dịch xong thì Menu của game sẽ hiện ra như này:

![Pacman Pause Menu](https://github.com/vovanhai2005/Pacman_V2/assets/142618703/6a3a4730-98fe-46d1-9d89-65d1a8119c01)

Menu sẽ bao gồm các tính năng:
* **New Game**: bắt đầu một game mới
* **How To Play**: hướng dẫn cách chơi
* **Highscore**: Xem bảng xếp hạng điểm
* **SOUND: ON/OFF**: Bật/Tắt âm thanh game
* **Quit**: Thoát game

## 2.2 Khi vào New Game, người chơi sẽ được đưa đến màn hình chơi như sau:

![Game](https://github.com/vovanhai2005/Pacman_V2/assets/142618703/0ec8243a-bc23-4b5e-b4b7-16a4e3314310)

## 2.2 Khi vào How To PLay, người chơi sẽ được đưa đến bảng hướng dẫn như sau:

# 3. Nhân vật, kẻ địch và item của game
## 3.1 Nhân vật
* Pacman:  ![pacman](https://github.com/vovanhai2005/Pacman_V2/assets/142618703/3bae88ec-0e63-4dcf-93f3-c6d53637ea46)
## 3.2 Kẻ địch
* Blinky: ![Blinky](https://github.com/vovanhai2005/Pacman_V2/assets/142618703/331a8e52-7eea-4c54-97f3-7b5264d28772)
* Pinky: ![Pinky](https://github.com/vovanhai2005/Pacman_V2/assets/142618703/10cca7bb-9ad7-4fd2-bd42-a71eb78014f8)
* Inky: ![Inky](https://github.com/vovanhai2005/Pacman_V2/assets/142618703/7b2001b8-10d9-4042-8100-ea6cc3bda794)
* Clyde: ![Clyde](https://github.com/vovanhai2005/Pacman_V2/assets/142618703/d727dde0-4e98-4d9e-8563-b43732e9fabd)
## 3.3 Item
* Bom: ![bombb](https://github.com/vovanhai2005/Pacman_V2/assets/142618703/53de97ec-8e1e-4257-9c31-42517f1eb483)
* Thanh laser ngang: ![Row_bomb](https://github.com/vovanhai2005/Pacman_V2/assets/142618703/b10e7125-80ea-44f0-a11e-f79fa9b2adea)
* Thanh laser dọc: ![Col_Bomb](https://github.com/vovanhai2005/Pacman_V2/assets/142618703/33317ccb-e902-4884-910e-f55776f58e63)
# 4. Hướng dẫn chơi game
* Sử dụng các nút ![wasd](https://github.com/vovanhai2005/Pacman_V2/assets/142618703/c7674494-d742-4006-ae75-174dc78cb070) hoặc để di chuyển Pacman tránh né ma
* Sử dụng nút z để kích hoạt quả bom gây sát thương lên toàn bộ hàng ngang và hàng dọc trong map
* Đạt đến level không giới hạn và tích lũy điểm cao nhất
# 5. Source Code
1. Folder Main
   * File Game.cpp: Khởi tạo màn hình game và quản lí các thao tác khởi tạo, chạy game và thoát game.
   * File GameControl.cpp: Quản lí chương trình chạy chính Operator, menu ngoài game và menu giữa game
   * File Operator.cpp: Quản lí tất cả các hoạt động chính của chương trình
2. Folder Manage
   * File Button.cpp: Quản lí nút bấm, khởi tạo các nút bấm của chương trình
   * File GameItemManage.cpp: Quản lí các thông tin như mạng sống, số điểm, số lượng ma đã ăn, số lượng xu đã ăn của các object trong chương trình
   * File Menu.cpp: Quản lí menu của chương trình bao gồm khởi tạo trò chơi mới, hướng dẫn chơi, bảng xếp hạng điểm số, tắt bật âm thanh và thoát game
   * File SoundManage.cpp: Quản lí âm thanh của cả chương trình
   * File TextManage.cpp: Quản lí render text cho chương trình
3. Folder Map
   * File Map.cpp: Quản lí việc tạo Map cho chương trình đồng thời khởi tạo giá trị đường đi cho chương trình. Trong file này có sử dụng kết hợp 2 vòng for vị trí và thuật toán BFS để loang 4 phía của điểm để tìm đường đi ngắn nhất giữa 2 ô bất kì ở trong map.
   * File PacMan_Map.txt: Thông số các tile của map được tạo bởi ảnh cho trước
4. Folder Object
   * File Bomb.cpp: Khởi tạo bom và vụ nổ lan xung quanh 4 đường đi tiêu diệt ma
   * File Ghost.cpp: Khởi tạo vị trí của ma, tạo các trạng thái frighten và scattering của ma đồng thời hồi sinh ma
   * File Pacman.cpp: Khởi tạo ví trí của Pacman, kiểm soát di chuyển, dừng lại và quản lí lối đi, lối rẽ gần vị trí Pacman nhất
   * File Object.cpp: Khởi tạo các đặc điểm chung của cả Pacman và Ghost như chết, lấy vị trí, đặt trạng thái, đi qua hầm,...
# 6. Cải tiến của game
So với phiên bản cổ điển, game đã được chỉnh sửa để quá trình chơi game trở nên mượt hơn. Việc sử dụng thuật toán BFS so với việc dùng khoảng cách Euclid để tìm đường đi giữa hai điểm đã đẩy tiến độ của trò chơi lên cao hơn. Ngoài ra, độ đa dạng của game đã được cải thiện như việc thêm tính năng đặt bom cho Pacman nhằm tiêu diệt ma nhanh hơn đồng thời hồi sinh ma ngay lập tức nhằm cân bằng độ khó cho game. Do thời gian có hạn nên game vẫn chưa có nhiều cải tiến hơn. Một số ý tưởng cải tiến game có thể bao gồm việc thêm các tính năng cho ma và có thể tạo ra người chơi pacman thứ 2.

# 7. Nguồn tham khảo và tài liệu:
* Tham khảo: Những kiến thức nền tảng cũng như các ý tưởng xây dựng game mình đều học thông qua channel Youtube [Phát Triển Phần Mềm 123A_Z](https://www.youtube.com/@PhatTrienPhanMem123AZ) và [Let's Make Games](https://www.youtube.com/@CarlBirch). Ngoài ra mình cũng có tham khảo nguồn tài liệu từ [LazyFoo](https://lazyfoo.net/tutorials/SDL/) và một số github repository tương tự
* Hình ảnh: Mình sử dụng một số ảnh từ [Pinterest](https://www.pinterest.com/) và một số còn lại mình dùng nguồn dữ liệu từ [Canva](https://www.canva.com/vi_vn/). Ngoài ra mình còn dùng  web [Remomve Background AI](https://remove-bg.ai/vi) để xóa nền
* Âm thanh: Mình lấy âm thanh từ trang [Sound Bible](https://soundbible.com/)
# 8. Phần kết
Em xin gửi lời cảm ơn chân thành đến:
* Thầy Lê Đức Trọng vì đã giúp em hiểu được cốt lõi của kiến thức lập trình nâng cao, hiểu quy trình và kỹ năng quản lý dự án nhằm qua đó nâng cao kến thức và xây dựng nền móng cơ bản trong việc hoàn thành game của em.
* Thầy Trần Trường Thủy vì đã hướng dẫn em những kiến thức cơ bản về lập trình game bằng SDL2 đồng thời tận tình chỉ bảo chúng em những công cụ cần thiết cho việc xây dựng project game này
* Mentor Nguyễn Vũ Thanh Tùng vì đã giúp em trong việc fix bug và hướng dẫn em fix một số code error trong game

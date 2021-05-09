1.	Hướng dẫn cài đặt
-	Tải thư viện SDL_Lib: [ https://bit.ly/3vTJdSu ]
-	Chạy chương trình .exe trong Debug
2.	Thuật toán
-	Các chương trình quản lý: nhân vật, địch, đạn bắn, ảnh va chạm, mạng nhân vật, text.
-	Điều khiển nhân vật: Nhận sự kiện từ chuột và bàn phím
•	Di chuyển bằng 4 phím mũi tên, cập nhật vị trí mới và load ảnh nhân vật
•	Bắn đạn bằng chuột trái và phải: Tạo list danh sách đạn bắn khi còn giữ chuột. Kiểm tra đạn có trong danh sách hay không và kiểm tra va chạm giữa các đối tượng, vượt quá màn hình -> xóa đạn.
-	Tạo kẻ địch:
•	Tạo vị trí xuất hiện địch random và đạn kèm theo
•	Đạn di chuyển từ phải qua trái, nếu đạn chạm hết màn hình thì quay lại vị trí địch tương ứng.
-	Xử lý va chạm giữa 2 đối tượng thông qua chỉ số left, right, top, bot của 2 đối tượng (4 trường hợp va chạm)
-	Tạo số mạng cho nhân vật, text thời gian, điểm số, mục tiêu game.
-	Địch xuất hiện, nhân vật và địch cùng di chuyển. Kiểm tra va chạm:  Nhân vật và địch; Nhân vật và đạn địch; Đạn nhân vật và địch;  
+ Xử lý nhân vật: Hiệu ứng va chạm, giảm số mạng, bất tử 3s, về vị trí ban đầu, kiểm tra số mạng và các mục tiêu.
+ Xử lý địch: Hiệu ứng va chạm, xóa địch và đạn
3.	Cách chơi
-	Điều khiển nhân vật bằng 4 phím mũi tên; bắn đạn bằng chuột
-	Nhân vật bắn đạn và dịch chuyển, tiêu diệt địch.
-	Người chơi tiêu diệt 1 địch tương ứng 1 điểm, vượt qua các mục tiêu của game đề ra. Nếu không vượt qua mục tiêu đạt được số điểm trong thời gian quy định hoặc hết số mạng va chạm thì game over.

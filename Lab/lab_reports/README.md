# Báo cáo lab dùng chung một project

Project này giữ `hcmut-report.cls`, bìa và kiểu trình bày từ template HCMUT. Tệp chính để biên dịch trên Overleaf là **`report.tex`**.

## Chuyển lab

Mở `source/content/select_lab.tex` và sửa đúng một dòng, ví dụ `\def\SelectedLab{lab01}` thành `\def\SelectedLab{lab02}`. `report.tex` tự nạp đúng file bìa `lab02-meta.tex` và file nội dung `lab02.tex`. Không cần tạo project Overleaf mới.

Các file `lab01.tex` đến `lab07.tex` nằm chung trong `source/content/`. Lab 1 là báo cáo đã làm với đủ 10 Exercise và ảnh ở `source/picture/bai_1/`. Lab 2–7 được chuyển từ các file `bai_2.tex` đến `bai_7.tex` cũ để tiện tiếp tục làm. Lab 4 và Lab 7 hiện chỉ có tiêu đề; Lab 8–9 trong bộ cũ để trống. Các file này chưa phải kết quả đã hoàn thành.

Để thêm lab mới, sao chép `lab-template.tex` thành `lab08.tex` và `lab-template-meta.tex` thành `lab08-meta.tex`, rồi sửa `select_lab.tex` sang `lab08`. Đặt ảnh dưới `source/picture/` và dùng đường dẫn tính từ thư mục gốc. Video Lab 1 đang là link GitHub nên không cần import clip.

## Bản cũ

Toàn bộ tệp còn lại của `[LATEX]MCU_LAB` được lưu nguyên trong `legacy_previous_report.zip` để không mất nội dung cũ. Đây chỉ là bản lưu trữ; project đang dùng `report.tex` và `hcmut-report.cls` của template HCMUT. ZIP tải lên Overleaf được tạo riêng và không chứa bản lưu trữ hay video.

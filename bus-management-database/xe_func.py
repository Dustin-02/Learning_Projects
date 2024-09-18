import _tkinter
import os
import shlex
from tkinter import filedialog
import tkinter as tk
from tkinter import ttk
from tkinter import messagebox
import mysql.connector


db = mysql.connector.connect(user='root', password='Dayjin_99', host='localhost', database='xe2')
cursor = db.cursor()

class App:
    def __init__(self, root):
        self.root = root
        self.root.title("Dữ liệu Khách hàng")
        self.root.geometry("400x500")

        # Tạo nút để mở cửa sổ với bảng dữ liệu
        open_button = tk.Button(root, text="Mở bảng dữ liệu", command=self.open_data_khach_hang)
        open_button.grid(row=0, column=0, columnspan=1, pady=10)
        # Tạo nút "Thêm khách hàng"
        add_button = tk.Button(root, text="Thêm khách hàng", command=self.add_customer_window)
        add_button.grid(row=0, column=1, columnspan=1, pady=10)

        self.entry_var = tk.StringVar()
        entry = tk.Entry(root, textvariable=self.entry_var)
        entry.grid(row=1, column=0, columnspan=1, pady=10)

        run_button = tk.Button(root, text="Chạy", command=self.run_query)
        run_button.grid(row=1, column=1, columnspan=1, pady=10)

        self.listbox = tk.Listbox(root, width=50, height=10)
        self.listbox.grid(row=2, column=0, columnspan=2, pady=10)

        root.columnconfigure(0, weight=1)
        root.columnconfigure(1, weight=1)
        root.columnconfigure(2, weight=1)
    def on_closing(self):
        if messagebox.askokcancel("tắt", "bạn có thật sự muốn tắt?"):
            self.destroy()

    def open_data_khach_hang(self):
        # Tạo cửa sổ con cho bảng dữ liệu
        data_window = tk.Toplevel(self.root)
        data_window.title("Dữ liệu Khách hàng")

        # Tạo Treeview để hiển thị dữ liệu
        tree = ttk.Treeview(data_window)
        tree["columns"] = ("STT", "HoVaTen", "CCCD", "MaKH", "Email", "NgaySinh", "SDT", "TrangThai")

        # Đặt tên cột và định dạng cột
        tree.column("#0", width=0, stretch=tk.NO)
        tree.column("STT", anchor='c', width=50)
        tree.column("HoVaTen", anchor='c', width=100)
        tree.column("CCCD", anchor='c', width=100)
        tree.column("MaKH", anchor='c', width=100)
        tree.column("Email", anchor='c', width=100)
        tree.column("NgaySinh", anchor='c', width=100)
        tree.column("SDT", anchor='c', width=100)
        tree.column("TrangThai", anchor='c', width=100)

        tree.heading("#0", text="", anchor='c')
        tree.heading("STT", text="STT", anchor='c')
        tree.heading("HoVaTen", text="Họ và Tên", anchor='c')
        tree.heading("CCCD", text="CCCD", anchor='c')
        tree.heading("MaKH", text="Mã KH", anchor='c')
        tree.heading("Email", text="Email", anchor='c')
        tree.heading("NgaySinh", text="Ngày Sinh", anchor='c')
        tree.heading("SDT", text="Số Điện Thoại", anchor='c')
        tree.heading("TrangThai", text="Trạng Thái", anchor='c')

        # Thêm dữ liệu STT vào Treeview
        cursor.execute("SELECT * FROM Khach_hang")
        rows = cursor.fetchall()

        for idx, row in enumerate(rows, start=1):
            tree.insert("", "end", values=(idx,) + row)

        # Đặt thanh cuộn
        scrollbar = ttk.Scrollbar(data_window, orient=tk.VERTICAL, command=tree.yview)
        tree.configure(yscroll=scrollbar.set)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

        # Bật tính năng sắp xếp cho mỗi cột
        for col in ("STT", "HoVaTen", "CCCD", "MaKH", "Email", "NgaySinh", "SDT", "TrangThai"):
            tree.heading(col, text=col, anchor='c', command=lambda c=col: self.sort_column(tree, c))

        tree.pack(pady=10)

    def sort_column(self, tv, col):
        # Lấy dữ liệu và kiểu dữ liệu của cột
        data = [(int(tv.set(k, col)) if col == "STT" else tv.set(k, col), k) for k in tv.get_children('')]

        # Sắp xếp theo giá trị
        data.sort()

        # Cập nhật Treeview
        for index, item in enumerate(data):
            tv.move(item[1], '', index)
    def add_customer_window(self):
        # Tạo cửa sổ con để thêm khách hàng
        add_window = tk.Toplevel(self.root)
        add_window.title("Thêm Khách hàng")

        # Tạo các thanh điền và nhãn cho các trường
        hovaten_label = tk.Label(add_window, text="Họ và Tên:")
        hovaten_entry = tk.Entry(add_window)

        cccd_label = tk.Label(add_window, text="CCCD:")
        cccd_entry = tk.Entry(add_window)

        maKH_label = tk.Label(add_window, text="Mã KH:")
        maKH_entry = tk.Entry(add_window)

        email_label = tk.Label(add_window, text="Email:")
        email_entry = tk.Entry(add_window)

        ngaysinh_label = tk.Label(add_window, text="Ngày Sinh:")
        ngaysinh_entry = tk.Entry(add_window)

        sdt_label = tk.Label(add_window, text="Số Điện Thoại:")
        sdt_entry = tk.Entry(add_window)

        # Đặt các thanh điền và nhãn trong cửa sổ con
        maKH_label.grid(row=0, column=0, padx=5, pady=5, sticky="e")
        maKH_entry.grid(row=0, column=1, padx=5, pady=5)

        hovaten_label.grid(row=1, column=0, padx=5, pady=5, sticky="e")
        hovaten_entry.grid(row=1, column=1, padx=5, pady=5)

        cccd_label.grid(row=2, column=0, padx=5, pady=5, sticky="e")
        cccd_entry.grid(row=2, column=1, padx=5, pady=5)

        email_label.grid(row=3, column=0, padx=5, pady=5, sticky="e")
        email_entry.grid(row=3, column=1, padx=5, pady=5)

        ngaysinh_label.grid(row=4, column=0, padx=5, pady=5, sticky="e")
        ngaysinh_entry.grid(row=4, column=1, padx=5, pady=5)

        sdt_label.grid(row=5, column=0, padx=5, pady=5, sticky="e")
        sdt_entry.grid(row=5, column=1, padx=5, pady=5)

        # Tạo nút "Tạo" để thực hiện thủ tục và đóng cửa sổ con
        button_them = tk.Button(add_window, text="tạo", command=lambda: self.create_customer(
            hovaten_entry.get(),
            cccd_entry.get(),
            maKH_entry.get(),
            email_entry.get(),
            ngaysinh_entry.get(),
            sdt_entry.get(),
            add_window
        ))
        button_them.grid(row=6, column=0, columnspan=1, pady=10)

        button_sua = tk.Button(add_window, text="sửa", command=lambda: self.update_customer(
            hovaten_entry.get(),
            cccd_entry.get(),
            maKH_entry.get(),
            email_entry.get(),
            ngaysinh_entry.get(),
            sdt_entry.get(),
            add_window
        ))
        button_sua.grid(row=7, column=0, columnspan=1, pady=10)

        button_xoa = tk.Button(add_window, text="xóa", command=lambda: self.delete_customer(
            maKH_entry.get(),
            add_window
        ))
        button_xoa.grid(row=6, column=1, columnspan=2, pady=10)

        button_unblock = tk.Button(add_window, text="bỏ chặn", command=lambda: self.unblock_customer(
            maKH_entry.get(),
            add_window
        ))
        button_unblock.grid(row=7, column=1, columnspan=2, pady=10)



    def create_customer(self, hovaten, cccd, maKH, email, ngaysinh, sdt, add_window):
        try:
            sql = "CALL INSERT_KH(%s, %s, %s, %s, %s, %s, @result)"
            data = (hovaten, cccd, maKH, email, ngaysinh, sdt)
            # Thực hiện truy vấn
            cursor.execute(sql, data)
            # Lấy kết quả từ biến session
            cursor.execute("SELECT @result")
            result_set = cursor.fetchall()
            if result_set:
                messagebox.showinfo("Kết quả", result_set[0][0])
            else:
                messagebox.showerror("Lỗi", "Đã xảy ra lỗi khi thực hiện thủ tục.")
            # Đóng cửa sổ con và commit thay đổi vào cơ sở dữ liệu
            add_window.destroy()
            db.commit()
        except Exception as e:
            messagebox.showerror("Lỗi", f"Đã xảy ra lỗi: {str(e)}")

    def update_customer(self, hovaten, cccd, maKH, email, ngaysinh, sdt, add_window):
        try:
            sql = "CALL UPDATE_KH(%s, %s, %s, %s, %s, %s, @result)"
            data = (hovaten, cccd, maKH, email, ngaysinh, sdt)
            # Thực hiện truy vấn
            cursor.execute(sql, data)
            # Lấy kết quả từ biến session
            cursor.execute("SELECT @result")
            result_set = cursor.fetchall()
            if result_set:
                messagebox.showinfo("Kết quả", result_set[0][0])
            else:
                messagebox.showerror("Lỗi", "Đã xảy ra lỗi khi thực hiện thủ tục.")
            # Đóng cửa sổ con và commit thay đổi vào cơ sở dữ liệu
            add_window.destroy()
            db.commit()
        except Exception as e:
            messagebox.showerror("Lỗi", f"Đã xảy ra lỗi: {str(e)}")

    def delete_customer(self,maKH, add_window):
        try:
            sql = "CALL DELETE_KH(%s, @result)"
            data = (maKH,)
            # Thực hiện truy vấn
            cursor.execute(sql, data)
            # Lấy kết quả từ biến session
            cursor.execute("SELECT @result")
            result_set = cursor.fetchall()
            if result_set:
                messagebox.showinfo("Kết quả", result_set[0][0])
            else:
                messagebox.showerror("Lỗi", "Đã xảy ra lỗi khi thực hiện thủ tục.")
            # Đóng cửa sổ con và commit thay đổi vào cơ sở dữ liệu
            add_window.destroy()
            db.commit()
        except Exception as e:
            messagebox.showerror("Lỗi", f"Đã xảy ra lỗi: {str(e)}")

    def unblock_customer(self, thamso, add_window):
        try:
            sql = "CALL UNBLOCK_KH(%s, @result)"
            data = (maKH,)
            # Thực hiện truy vấn
            cursor.execute(sql, data)
            # Lấy kết quả từ biến session
            cursor.execute("SELECT @result")
            result_set = cursor.fetchall()
            if result_set:
                messagebox.showinfo("Kết quả", result_set[0][0])
            else:
                messagebox.showerror("Lỗi", "Đã xảy ra lỗi khi thực hiện thủ tục.")
            # Đóng cửa sổ con và commit thay đổi vào cơ sở dữ liệu
            add_window.destroy()
            db.commit()
        except Exception as e:
            messagebox.showerror("Lỗi", f"Đã xảy ra lỗi: {str(e)}")

    def run_query(self):
        self.listbox.delete(0, tk.END)
        value = self.entry_var.get()
        values = value.split()
        thamso = space_empty(value)
        if (value.startswith('kpi ')):
            if (thamso == 1):
                val = value[4:]
                print(val)
                try:
                    sql = "select KPI_tuyen_xe(%s,%s)"
                    data = (values[1], values[2],)
                    cursor.execute(sql, data)
                    result_set = cursor.fetchall()
                    if result_set:
                        messagebox.showinfo("Kết quả", result_set[0][0])
                    else:
                        messagebox.showerror("Lỗi", "Đã xảy ra lỗi khi thực hiện hàm.")
                    # Đóng cửa sổ con và commit thay đổi vào cơ sở dữ liệu
                    db.commit()
                except Exception as e:
                    messagebox.showerror("Lỗi", f"Đã xảy ra lỗi: {str(e)}")
            else:
                self.print_c("hàm này cần tham số user")

        elif (value.startswith('che ')):
            if (thamso == 1):
                val = value[4:]
                print(val)
                try:
                    sql = "select check_cost_nhan_su(%s,%s,%s)"
                    data = (values[1], values[2], values[3],)
                    cursor.execute(sql, data)
                    result_set = cursor.fetchall()
                    if result_set:
                        messagebox.showinfo("Kết quả", result_set[0][0])
                    else:
                        messagebox.showerror("Lỗi", "Đã xảy ra lỗi khi thực hiện hàm.")
                    # Đóng cửa sổ con và commit thay đổi vào cơ sở dữ liệu
                    db.commit()
                except Exception as e:
                    messagebox.showerror("Lỗi", f"Đã xảy ra lỗi: {str(e)}")
            else:
                self.print_c("hàm này cần tham số user")

        elif (value.startswith('getemp ')):
            if (thamso == 1):
                val = value[7:]
                print(val)
                try:
                    sql = "CALL GetEmployeeSalesInfoM(%s, %s, %s)"
                    data = (values[1], values[2], values[3],)
                    cursor.execute(sql, data)
                    result_set = cursor.fetchall()
                    if result_set:
                        messagebox.showinfo("Kết quả", result_set[0][0])
                    else:
                        messagebox.showerror("Lỗi", "Đã xảy ra lỗi khi thực hiện thủ tục.")
                    # Đóng cửa sổ con và commit thay đổi vào cơ sở dữ liệu
                    db.commit()
                except Exception as e:
                    messagebox.showerror("Lỗi", f"Đã xảy ra lỗi: {str(e)}")
            else:
                self.print_c("thủ tục này cần tham số user")

        elif (value.startswith('calc ')):
            if (thamso == 1):
                val = value[5:]
                print(val)
                try:
                    sql = "CALL CalculateSomething(%s, %s)"
                    data = (values[1], values[2],)
                    cursor.execute(sql, data)
                    result_set = cursor.fetchall()
                    if result_set:
                        messagebox.showinfo("Kết quả", result_set[0][0])
                    else:
                        messagebox.showerror("Lỗi", "Đã xảy ra lỗi khi thực hiện thủ tục.")
                    # Đóng cửa sổ con và commit thay đổi vào cơ sở dữ liệu
                    db.commit()
                except Exception as e:
                    messagebox.showerror("Lỗi", f"Đã xảy ra lỗi: {str(e)}")
            else:
                self.print_c("thủ tục này cần tham số user")
        else:
            self.print_c('bạn có thể nhập các hàm')

    def print_c(self, x):
        max_length = 50
        while len(x) > max_length:
            part, x = x[:max_length], x[max_length:]
            if x and x[0] == ",":
                part += x[0]  # Thêm dấu ',' vào cuối phần trước
                x = x[1:]  # Bỏ dấu ',' khỏi đầu chuỗi x
            self.listbox.insert(tk.END, part)
        self.listbox.insert(tk.END, x)


def space_empty(s):

    parts = s.split(" ")

    if len(parts) > 1:

        if parts[1]:
            return True  # Có khoảng trắng và sau khoảng trắng không rỗng
    return False  # Không có khoảng trắng hoặc sau khoảng trắng rỗng

# Tạo ứng dụng và mainloop
root = tk.Tk()
app = App(root)
root.mainloop()

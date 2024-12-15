DROP PROCEDURE IF EXISTS INSERT_KH; 
DROP PROCEDURE IF EXISTS UPDATE_KH; 
DROP PROCEDURE IF EXISTS DELETE_KH;
DROP PROCEDURE IF EXISTS UNBLOCK_KH;
DROP PROCEDURE IF EXISTS InsertVeXeHanhKhach; 
DROP PROCEDURE IF EXISTS InsertVeXeVanChuyenHang; 
DROP PROCEDURE IF EXISTS GetEmployeeSalesInfo;
DROP PROCEDURE IF EXISTS GetEmployeeSalesInfoM;
DROP PROCEDURE IF EXISTS CalculateSomething; 

DELIMITER $$
CREATE PROCEDURE INSERT_KH(
    IN ihovaten VARCHAR(30),
    IN icccd VARCHAR(12),
    IN imaKH VARCHAR(9),
    IN iEmail VARCHAR(50),
    IN ingaysinh DATE,
    IN isdt VARCHAR(10),
    OUT oResult VARCHAR(255)
)
BEGIN
    IF TIMESTAMPDIFF(YEAR, ingaysinh, CURDATE()) >= 18 THEN
        -- Kiểm tra xem mã khách hàng đã tồn tại chưa
        IF NOT EXISTS (SELECT 1 FROM Khach_hang WHERE maKH = imaKH) THEN
            INSERT INTO Khach_hang (hovaten, cccd, maKH, Email, ngaysinh, sdt, trang_thai)
            VALUES (ihovaten, icccd, imaKH, iEmail, ingaysinh, isdt, '0');

            SET oResult = 'Them thong tin khach hang thanh cong';
        ELSE
            SET oResult = 'Ma khach hang da ton tai. Vui long chon ma khac';
        END IF;
    ELSE
        SET oResult = 'Khach hang phai du 18 tuoi, moi co the dat ve';
    END IF;
END $$
DELIMITER ;

-- cap nhat thong tin
DELIMITER $$
CREATE PROCEDURE UPDATE_KH (
    IN newHovaten VARCHAR(30),
    IN newCccd VARCHAR(12),
    IN nmaKH VARCHAR(9),
    IN newEmail VARCHAR(50),
    IN newNgaysinh DATE,
    IN newSdt VARCHAR(10),
    OUT oResult VARCHAR(255)
)
BEGIN
    -- Kiểm tra xem khách hàng có tồn tại không
    IF (SELECT COUNT(*) FROM Khach_hang WHERE maKH = nmaKH) > 0 THEN
        -- Kiểm tra xem trạng thái hiện tại và trạng thái mới có hợp lệ không
        IF (SELECT trang_thai FROM Khach_hang WHERE maKH = nmaKH) NOT IN ('2') THEN
            -- Cập nhật thông tin khách hàng
            UPDATE Khach_hang
            SET hovaten = newHovaten,
                cccd = newCccd,
                Email = newEmail,
                ngaysinh = newNgaysinh,
                sdt = newSdt
            WHERE maKH = nmaKH;

            SET oResult = 'Cap nhap thong tin khach hang thanh cong';
        ELSE
            SET oResult = 'Khach hang da bi block, khong duoc phep cap nhap';
        END IF;
    ELSE
        SET oResult = CONCAT('Khong ton tai khach hang ', nmaKH, '.');
    END IF;
END $$

DELIMITER ;

-- xoa kh

DELIMITER $$

CREATE PROCEDURE DELETE_KH(IN imaKH VARCHAR(9), OUT oResult VARCHAR(255))
BEGIN
	DECLARE currentTrang_thai varchar(1);
    -- Kiểm tra xem khách hàng có tồn tại không
    IF EXISTS (SELECT 1 FROM Khach_hang WHERE maKH = maKH) THEN
        -- Lấy trạng thái hiện tại của khách hàng
        SELECT trang_thai INTO currentTrang_thai FROM Khach_hang WHERE maKH = imaKH;

        -- Kiểm tra xem trạng thái hiện tại có hợp lệ không
        IF currentTrang_thai ='0' THEN
			DELETE FROM Khach_hang WHERE maKH = imaKH;
            SET oResult = 'đã xóa khách hàng';
        ELSEIF currentTrang_thai ='1' THEN
			UPDATE Khach_hang SET trang_thai = '2' WHERE maKH = imaKH;
			SET oResult = 'đã block khách hàng';
        ELSEIF currentTrang_thai = '2' then
            SET oResult = 'Không được phép xóa khách hàng, khách đang bị block';
		ELSE 
			SET oResult = CONCAT('có gì đó sai sai ', nmaKH, '.');
        END IF;
    ELSE
        SET oResult = CONCAT('Khong ton tai khach hang ', nmaKH, '.');
    END IF;
END $$

DELIMITER ;
-- -- ************************************************************************************************************************
DELIMITER $$
CREATE PROCEDURE UNBLOCK_KH(
    IN imaKH VARCHAR(9), OUT oResult VARCHAR(255)
)
BEGIN
    -- Kiểm tra xem khách hàng có tồn tại không
    DECLARE currentTrang_thai varchar(1);
    IF EXISTS (SELECT 1 FROM Khach_hang WHERE maKH = imaKH) THEN       
        SELECT trang_thai INTO currentTrang_thai FROM Khach_hang WHERE maKH = imaKH;
        -- Kiểm tra xem trạng thái hiện tại
        IF currentTrang_thai IN ('0', '1') THEN
            SET oResult = 'khách hàng có trạng thái bình thường';
        ELSEIF currentTrang_thai = '2' THEN
            -- Cập nhật trạng thái mới
            UPDATE Khach_hang
            SET trang_thai = '1'
            WHERE maKH = imaKH;
            SET oResult = 'đã mở khóa khách hàng';
        END IF;
    ELSE
        SET oResult = CONCAT('Khong ton tai khach hang ', imaKH, '.');
    END IF;
END $$
DELIMITER ;

-- ---------------------------------------------------------------------------------------------------------------------------------------------

-- -------------------------------------------------------------------------------------------------------------------------------------------------
DELIMITER $$

CREATE PROCEDURE InsertVeXeHanhKhach(
    IN p_masove VARCHAR(9),
    IN p_tramdi VARCHAR(1),
    IN p_tramden VARCHAR(1),
    IN p_tuyendi VARCHAR(30),
    IN p_ngaygiodi DATETIME,
    IN p_maxe VARCHAR(6),
    IN p_maKH VARCHAR(9),
    IN p_manv VARCHAR(9),
    IN p_thoigiandatve DATETIME,
    IN p_tongtien DECIMAL(10,2),
    IN p_sogiuong INT
)
BEGIN
    -- Insert thông tin vào bảng ve_xe
    INSERT INTO ve_xe (masove, tramdi, tramden, tuyendi, ngaygiodi, maxe, maKH, manv, thoigiandatve, tongtien)
    VALUES (p_masove, p_tramdi, p_tramden, p_tuyendi, p_ngaygiodi, p_maxe, p_maKH, p_manv, p_thoigiandatve, p_tongtien);

    -- Insert thông tin vào bảng hanh_khach
    INSERT INTO hanh_khach (masove, sogiuong)
    VALUES (p_masove, p_sogiuong);
END $$



DELIMITER ;

DELIMITER $$

CREATE PROCEDURE InsertVeXeVanChuyenHang(
    IN p_masove VARCHAR(9),
    IN p_tramdi VARCHAR(1),
    IN p_tramden VARCHAR(1),
    IN p_tuyendi VARCHAR(30),
    IN p_ngaygiodi DATETIME,
    IN p_maxe VARCHAR(6),
    IN p_maKH VARCHAR(9),
    IN p_manv VARCHAR(9),
    IN p_thoigiandatve DATETIME,
    IN p_tongtien DECIMAL(10,2),
    IN p_SDTNguoiNhan VARCHAR(10),
    IN p_tenNguoiNhan VARCHAR(30),
    IN p_khoiLuong INT,
    IN p_dai FLOAT,
    IN p_rong FLOAT,
    IN p_cao FLOAT,
    IN p_luuy VARCHAR(20),
    IN p_chiphi DECIMAL(10,2)
)
BEGIN
    -- Insert thông tin vào bảng ve_xe
    INSERT INTO ve_xe (masove, tramdi, tramden, tuyendi, ngaygiodi, maxe, maKH, manv, thoigiandatve, tongtien)
    VALUES (p_masove, p_tramdi, p_tramden, p_tuyendi, p_ngaygiodi, p_maxe, p_maKH, p_manv, p_thoigiandatve, p_tongtien);

    -- Insert thông tin vào bảng van_chuyen_hang
    INSERT INTO van_chuyen_hang (masove, SDTNguoiNhan, tenNguoiNhan, khoiLuong, dai, rong, cao, luuy, chiphi)
    VALUES (p_masove, p_SDTNguoiNhan, p_tenNguoiNhan, p_khoiLuong, p_dai, p_rong, p_cao, p_luuy, p_chiphi);
END $$

DELIMITER ;


--  -----------------------------------------------------------------------------------

-- ------------------------------------------------------------------------------------

-- THỦ TỤC 1: 

DELIMITER $$

CREATE PROCEDURE GetEmployeeSalesInfo(IN employee_id VARCHAR(9))
BEGIN
    DECLARE total_tickets INT;
    DECLARE total_revenue DECIMAL(10, 2);

    -- Lấy tổng số vé và tổng doanh thu từ bảng ve_xe
    SELECT COUNT(*), SUM(tongtien) INTO total_tickets, total_revenue
    FROM ve_xe
    WHERE manv = employee_id;

    -- In kết quả
    SELECT total_tickets AS TotalTickets, total_revenue AS TotalRevenue;
    
END $$

DELIMITER ;

DELIMITER $$

CREATE PROCEDURE GetEmployeeSalesInfoM(IN employee_id VARCHAR(9), IN month_input INT,  IN year_input INT)
BEGIN
    DECLARE total_tickets INT;
    DECLARE total_revenue DECIMAL(10, 2);

    -- Lấy tổng số vé và tổng doanh thu từ bảng ve_xe
    SELECT COUNT(*), SUM(tongtien) INTO total_tickets, total_revenue
    FROM ve_xe
    WHERE manv = employee_id
    AND MONTH(thoigiandatve) = month_input
    and year(thoigiandatve) = year_input;

    -- In kết quả
    SELECT total_tickets AS TotalTickets, total_revenue AS TotalRevenue;
    
END $$

DELIMITER ;


-- THỦ TỤC 2: 
DELIMITER $$

CREATE PROCEDURE CalculateSomething(IN month_input INT, IN year_input INT)
BEGIN

    SELECT c.*, x.biensoxe, x.loaixe
	FROM Chay c
	JOIN xe x ON c.maxe = x.masoxe
	WHERE (c.giuongtrong / x.tonggiuong) < 0.5 and MONTH(ngaygiochuyen) = month_input AND YEAR(ngaygiochuyen) = year_input;

END $$

DELIMITER ;

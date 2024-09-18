DROP TRIGGER IF EXISTS update_tongtien_insert;
DELIMITER $$
CREATE TRIGGER update_tongtien_insert
AFTER INSERT ON hanh_khach
FOR EACH ROW
BEGIN
    DECLARE giadi DECIMAL(10,2);
    DECLARE giaden DECIMAL(10,2);
    
    -- Lấy giá từ bảng di_qua cho tramdi
    SELECT gia INTO giadi
    FROM di_qua
    WHERE tentram = (SELECT tramdi FROM ve_xe WHERE masove = NEW.masove)
        AND tentuyen = (SELECT tuyendi FROM ve_xe WHERE masove = NEW.masove);

    -- Lấy giá từ bảng di_qua cho tramden
    SELECT gia INTO giaden
    FROM di_qua
    WHERE tentram = (SELECT tramden FROM ve_xe WHERE masove = NEW.masove)
        AND tentuyen = (SELECT tuyendi FROM ve_xe WHERE masove = NEW.masove);

    -- Cập nhật giá tiền trong bảng ve_xe
    UPDATE ve_xe
    SET tongtien = NEW.sogiuong * (giaden - giadi)
    WHERE masove = NEW.masove;
END$$
DELIMITER ;


DROP TRIGGER IF EXISTS update_tongtien_delete;
DELIMITER $$
CREATE TRIGGER update_tongtien_delete
AFTER DELETE ON hanh_khach
FOR EACH ROW
BEGIN
    DECLARE giadi DECIMAL(10,2);
    DECLARE giaden DECIMAL(10,2);
    
    -- Lấy giá từ bảng di_qua cho tramdi
    SELECT gia INTO giadi
    FROM di_qua
    WHERE tentram = (SELECT tramdi FROM ve_xe WHERE masove = old.masove)
        AND tentuyen = (SELECT tuyendi FROM ve_xe WHERE masove = old.masove);

    -- Lấy giá từ bảng di_qua cho tramden
    SELECT gia INTO giaden
    FROM di_qua
    WHERE tentram = (SELECT tramden FROM ve_xe WHERE masove = old.masove)
        AND tentuyen = (SELECT tuyendi FROM ve_xe WHERE masove = old.masove);

    -- Cập nhật giá tiền trong bảng ve_xe
    UPDATE ve_xe
    SET tongtien = 0
    WHERE masove = old.masove;
END$$
DELIMITER ;


DROP TRIGGER IF EXISTS update_tongtien_update;
DELIMITER $$
CREATE TRIGGER update_tongtien_update
AFTER UPDATE ON hanh_khach
FOR EACH ROW
BEGIN
    DECLARE giadi DECIMAL(10,2);
    DECLARE giaden DECIMAL(10,2);
    
    -- Lấy giá từ bảng di_qua cho tramdi
    SELECT gia INTO giadi
    FROM di_qua
    WHERE tentram = (SELECT tramdi FROM ve_xe WHERE masove = NEW.masove)
        AND tentuyen = (SELECT tuyendi FROM ve_xe WHERE masove = NEW.masove);

    -- Lấy giá từ bảng di_qua cho tramden
    SELECT gia INTO giaden
    FROM di_qua
    WHERE tentram = (SELECT tramden FROM ve_xe WHERE masove = NEW.masove)
        AND tentuyen = (SELECT tuyendi FROM ve_xe WHERE masove = NEW.masove);

    -- Cập nhật giá tiền trong bảng ve_xe
    UPDATE ve_xe
    SET tongtien = NEW.sogiuong * (giaden - giadi)
    WHERE masove = NEW.masove;
END$$
DELIMITER ;

-- van chuyen hang 
DROP TRIGGER IF EXISTS update_tongtien2_insert;
DELIMITER $$
CREATE TRIGGER update_tongtien2_insert
AFTER INSERT ON van_chuyen_hang
FOR EACH ROW
BEGIN
    -- Cập nhật giá tiền trong bảng ve_xe
    UPDATE ve_xe
    SET tongtien = NEW.chiphi
    WHERE masove = NEW.masove;
END$$
DELIMITER ;

DROP TRIGGER IF EXISTS update_tongtien2_delete;
DELIMITER $$
CREATE TRIGGER update_tongtien2_delete
AFTER DELETE ON van_chuyen_hang
FOR EACH ROW
BEGIN
    -- Cập nhật giá tiền trong bảng ve_xe
    UPDATE ve_xe
    SET tongtien = old.chiphi
    WHERE masove = old.masove;
END$$
DELIMITER ;

DROP TRIGGER IF EXISTS update_tongtien2_update;
DELIMITER $$
CREATE TRIGGER update_tongtien2_update
AFTER UPDATE ON van_chuyen_hang
FOR EACH ROW
BEGIN
    -- Cập nhật giá tiền trong bảng ve_xe
    UPDATE ve_xe
    SET tongtien = NEW.chiphi
    WHERE masove = NEW.masove;
END$$
DELIMITER ;


-- trigger 2

DROP TRIGGER IF EXISTS update_giuongtrong_insert;
DELIMITER $$
CREATE TRIGGER update_giuongtrong_insert
AFTER INSERT ON hanh_khach
FOR EACH ROW
BEGIN
    DECLARE maxe_var VARCHAR(6);
    DECLARE tentuyen_var VARCHAR(30);
    DECLARE ngaygiochuyen_var DATETIME;
    
    -- Lấy thông tin từ bảng ve_xe dựa trên masove
    SELECT maxe, tuyendi, ngaygiodi
    INTO maxe_var, tentuyen_var, ngaygiochuyen_var
    FROM ve_xe
    WHERE masove = NEW.masove;

    -- Cập nhật số giường trống trong bảng Chay
    UPDATE Chay
    SET giuongtrong = giuongtrong - NEW.sogiuong
    WHERE maxe = maxe_var AND tentuyen = tentuyen_var AND ngaygiochuyen = ngaygiochuyen_var;
END $$
DELIMITER ;


DROP TRIGGER IF EXISTS update_giuongtrong_delete;
DELIMITER $$
CREATE TRIGGER update_giuongtrong_delete
AFTER delete ON hanh_khach
FOR EACH ROW
BEGIN
    DECLARE maxe_var VARCHAR(6);
    DECLARE tentuyen_var VARCHAR(30);
    DECLARE ngaygiochuyen_var DATETIME;
    
    -- Lấy thông tin từ bảng ve_xe dựa trên masove
    SELECT maxe, tuyendi, ngaygiodi
    INTO maxe_var, tentuyen_var, ngaygiochuyen_var
    FROM ve_xe
    WHERE masove = OLD.masove;

    -- Cập nhật số giường trống trong bảng Chay
    UPDATE Chay
    SET giuongtrong = giuongtrong + OLD.sogiuong
    WHERE maxe = maxe_var AND tentuyen = tentuyen_var AND ngaygiochuyen = ngaygiochuyen_var;
END $$
DELIMITER ;



DROP TRIGGER IF EXISTS update_giuongtrong_update;
DELIMITER $$
CREATE TRIGGER update_giuongtrong_update
AFTER UPDATE ON hanh_khach
FOR EACH ROW
BEGIN
    DECLARE maxe_var VARCHAR(6);
    DECLARE tentuyen_var VARCHAR(30);
    DECLARE ngaygiochuyen_var DATETIME;
    DECLARE sogiuong_old INT;
    DECLARE sogiuong_new INT;
    -- Lấy thông tin từ bảng ve_xe dựa trên masove (dữ liệu cũ)
    SELECT maxe, tuyendi, ngaygiodi, sogiuong
    INTO maxe_var, tentuyen_var, ngaygiochuyen_var, sogiuong_old
    FROM ve_xe
    WHERE masove = OLD.masove;
    -- Lấy thông tin từ bảng ve_xe dựa trên masove (dữ liệu mới)
    SELECT sogiuong
    INTO sogiuong_new
    FROM ve_xe
    WHERE masove = NEW.masove;
    -- Cập nhật số giường trống trong bảng Chay
    UPDATE Chay
    SET giuongtrong = giuongtrong + sogiuong_old - sogiuong_new
    WHERE maxe = maxe_var AND tentuyen = tentuyen_var AND ngaygiochuyen = ngaygiochuyen_var;
END $$

DELIMITER ;

-- tự động thêm giuong
DROP TRIGGER IF EXISTS insert_giuongxe_insert;
DELIMITER $$

CREATE TRIGGER insert_giuongxe_insert
AFTER insert ON chay
FOR EACH ROW
BEGIN
    INSERT INTO ma_giuong_xe (magiuong, maxe, tentuyen, ngaygiochuyen,tt)
	SELECT
		magiuong.magiuong,
        new.maxe,
		new.tentuyen,
		new.ngaygiochuyen,
        magiuong.tt
		
	FROM
		magiuong;
END $$
DELIMITER ;

-- cập nhật các giường trống
DROP TRIGGER IF EXISTS update_tt_ma_giuong_xe_insert;
DELIMITER $$

CREATE TRIGGER update_tt_ma_giuong_xe_insert
AFTER INSERT ON ma_giuong
FOR EACH ROW
BEGIN
    UPDATE ma_giuong_xe
    SET tt = '1'
    WHERE magiuong = NEW.magiuong
    AND maxe = (SELECT maxe FROM ve_xe WHERE masove = NEW.mave)
    AND tentuyen = (SELECT tuyendi FROM ve_xe WHERE masove = NEW.mave)
    AND ngaygiochuyen = (SELECT ngaygiodi FROM ve_xe WHERE masove = NEW.mave);
END $$

DELIMITER ;


DROP TRIGGER IF EXISTS update_tt_ma_giuong_xe_delete;
DELIMITER $$

CREATE TRIGGER update_tt_ma_giuong_xe_delete
AFTER delete ON ma_giuong
FOR EACH ROW
BEGIN
    UPDATE ma_giuong_xe
    SET tt = '0'
    WHERE magiuong = old.magiuong
    AND maxe = (SELECT maxe FROM ve_xe WHERE masove = old.mave)
    AND tentuyen = (SELECT tuyendi FROM ve_xe WHERE masove = old.mave)
    AND ngaygiochuyen = (SELECT ngaygiodi FROM ve_xe WHERE masove = old.mave);
END $$

DELIMITER ;


DROP TRIGGER IF EXISTS update_tt_ma_giuong_xe_update;
DELIMITER $$

CREATE TRIGGER update_tt_ma_giuong_xe_update
AFTER update ON ma_giuong
FOR EACH ROW
BEGIN
	UPDATE ma_giuong_xe
    SET tt = '1'
    WHERE magiuong = NEW.magiuong
    AND maxe = (SELECT maxe FROM ve_xe WHERE masove = NEW.mave)
    AND tentuyen = (SELECT tuyendi FROM ve_xe WHERE masove = NEW.mave)
    AND ngaygiochuyen = (SELECT ngaygiodi FROM ve_xe WHERE masove = NEW.mave);

    UPDATE ma_giuong_xe
    SET tt = '0'
    WHERE magiuong = old.magiuong
    AND maxe = (SELECT maxe FROM ve_xe WHERE masove = old.mave)
    AND tentuyen = (SELECT tuyendi FROM ve_xe WHERE masove = old.mave)
    AND ngaygiochuyen = (SELECT ngaygiodi FROM ve_xe WHERE masove = old.mave);
END $$

DELIMITER ;

-- chuyển trạng thái
DROP TRIGGER IF EXISTS update_trangthai_insert;
DELIMITER $$
CREATE TRIGGER update_trangthai_insert
AFTER INSERT ON ve_xe
FOR EACH ROW
BEGIN
    -- Lấy giá từ bảng di_qua cho tramdi
    UPDATE Khach_hang SET trang_thai = '1' WHERE maKH = new.maKH;
END$$
DELIMITER ;
 

 

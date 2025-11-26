# 📦 DreamLink Installation Guide

## วิธีติดตั้ง Library

### Option 1: Manual Installation (แนะนำ)

1. **ย้าย folder ไปที่ Arduino libraries:**
   ```bash
   # macOS/Linux
   cp -r fese-probe-261125 ~/Documents/Arduino/libraries/DreamLink

   # Windows
   # Copy folder fese-probe-261125 ไปที่:
   # C:\Users\<YourName>\Documents\Arduino\libraries\DreamLink
   ```

2. **เปิด Arduino IDE ใหม่**

3. **ทดสอบ:**
   - File → Examples → DreamLink → 01_BasicMovement
   - Upload ไปที่ ESP32

### Option 2: Symlink (สำหรับ Development)

```bash
# สร้าง symlink (macOS/Linux)
ln -s /path/to/fese-probe-261125 ~/Documents/Arduino/libraries/DreamLink

# ข้อดี: แก้ไข code ตรง repo ได้เลย ไม่ต้อง copy ซ้ำ
```

---

## ✅ ตรวจสอบว่าติดตั้งสำเร็จ

1. เปิด Arduino IDE
2. ไปที่ **Sketch → Include Library**
3. ต้องเห็น **DreamLink** ในรายการ
4. เลือก **File → Examples → DreamLink**
5. เห็น examples ทั้ง 5 ตัว

---

## 🎯 Quick Test

```cpp
#include <DreamLink.h>

DreamLink probe;

void setup() {
  probe.begin();
  probe.when(DISTANCE < 20).then(TURN_RIGHT, 120);
  probe.wakeup();
}

void loop() {
  probe.live();
}
```

**Upload → Open Serial Monitor (115200 baud)**

ถ้าเห็น:
```
========================================
   DreamLink - Where Physical Meets Meaning
========================================

[DreamLink] System initialized
[DreamLink] Awakened with 1 rules
```

แสดงว่า **ติดตั้งสำเร็จ!** 🎉

---

## ⚠️ Common Issues

### Issue 1: "DreamLink.h: No such file or directory"

**สาเหตุ:** Library ไม่ได้อยู่ที่ถูกต้อง

**แก้:**
1. ตรวจสอบ path: `~/Documents/Arduino/libraries/DreamLink/`
2. ใน folder ต้องมี: `src/`, `examples/`, `library.properties`
3. เปิด Arduino IDE ใหม่

### Issue 2: "undefined reference to `motorLeft`"

**สาเหตุ:** `globals.cpp` ไม่ถูก compile

**แก้:**
1. ตรวจสอบว่า `src/globals.cpp` มีอยู่
2. Verify → ดู log ว่า globals.cpp ถูก compile หรือไม่

### Issue 3: Examples หาไม่เจอ

**สาเหตุ:** Folder name ไม่ถูก

**แก้:**
- ต้องชื่อ `DreamLink` เท่านั้น (ไม่ใช่ `fese-probe-261125`)
- Rename folder แล้วเปิด IDE ใหม่

---

## 🔧 Board Configuration

ใน Arduino IDE:
- **Board:** ESP32 Dev Module (หรือ ESP32-S3)
- **Upload Speed:** 921600
- **Flash Frequency:** 80MHz
- **Partition Scheme:** Default
- **Port:** เลือก COM port ที่ถูกต้อง

---

## 📚 Next Steps

1. ลอง **Examples** ทั้ง 5 ตัว
2. อ่าน [LIBRARY_README.md](LIBRARY_README.md)
3. ปรับแต่ง `behavior/rules.h`
4. สนุกกับการ hack! 🚀

---

**มีปัญหา?** เปิด issue ที่ [GitHub](https://github.com/v1b3x0r/mds/issues)

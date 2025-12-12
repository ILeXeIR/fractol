# Fractol

Fractol is a graphical exploration tool for visualizing mathematical fractals, built entirely in **C** using the **MLX42** graphics library.  
The program renders several fractal sets in real time and allows you to navigate, zoom, and change color schemes interactively.

---

## 🚀 Features

- **Multiple fractals**: Mandelbrot, Julia, and BurningShip  
- **Smooth zooming** with mouse scroll  
- **Navigation** using arrow keys  
- **Dynamic color schemes** and palette cycling  
- **Parameter control**  
- **Stable, responsive rendering** with per-pixel calculations  

---

## 📚 About the Project

This project was developed as part of the Codam (42 Network) curriculum to practice:
- working with complex numbers  
- implementing iterative mathematical formulas  
- optimizing pixel rendering  
- handling graphical events in MLX42  
- writing clean, portable C code  

---

## 📜 About MLX42

This project uses MLX42, a modern OpenGL-based graphics library.
Per subject requirements, the full MLX42 library is included directly in this repository, not linked externally.

MLX42 official repository:

https://github.com/codam-coding-college/MLX42

---

## 🔧 Build and Run

**1.** Install all dependencies for MLX42 for you OS:
- [**Linux**](https://github.com/codam-coding-college/MLX42?tab=readme-ov-file#for-linux)
- [**macOS**](https://github.com/codam-coding-college/MLX42?tab=readme-ov-file#for-linux)
- [**Windows via WSL2**](https://github.com/codam-coding-college/MLX42?tab=readme-ov-file#for-linux)

**2.** Clone this repository.

**3.** Compile:
```
make
```

**4.** Run
```
./fractol [SET] [CX] [CY] [MAX_ITER]
```

[SET] - Available fractal types:
- `m` - Mandelbrot
- `j` - Julia
- `b` - BurningShip

Other parameters are optional.

[CX] [CY] - are two numbers for Julia set. Julia fractals take two parameters (real and imaginary values) that define the complex constant used to generate the shape of the fractal.

[MAX_ITER] - a number from 1 to 1000. Maximum iterations to calculate a color of each pixel.

Examples
```
./fractol m
./fractol j
./fractol j -0.7 0.27
```

---

## 🎮 Controls

Mouse
- Scroll ⬆️ → Zoom in, according to the cursor position
- Scroll ⬇️ → Zoom out, according to the cursor position

Keyboard
- ⬅️ ➡️ ⬆️ ⬇️ → Move around
- 1️⃣ 2️⃣ 3️⃣ 4️⃣ 5️⃣ → Switch color palette, five options
- ESC → Quit

---

## 📸 Preview

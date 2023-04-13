# Razer Blade Stealth Triple Boot

**Atualizações pós-instalação, para o tutorial completo visite: https://fxlip.com/building/perfect-laptop/**


Introdução
---

![Sobre esse Mac](https://github.com/fxlip/hackintosh/blob/master/imgs/about_mac.png)
![Sobre esse Windows](https://github.com/fxlip/hackintosh/blob/master/imgs/about_windows.png)
![Sobre esse Linux](https://github.com/fxlip/hackintosh/blob/master/imgs/about_kali.png)

O objetivo desse hackintosh foi criar um setup de desenvolvimento completo junto com windows e linux para ter todas as ferramentas de desenvolvimento disponíveis em todas as plataformas, facilitando testes e deploys de apps e designs. Agradeço aos guias do [k-sym](https://github.com/k-sym/Razer_Blade_Stealth_Late_2019_GTX_Hackintosh), [StoneEvil](https://github.com/stonevil/Razer_Blade_Advanced_early_2019_Hackintosh) e [tylernguyen](https://github.com/tylernguyen/razer15-hackintosh) que me encorajaram a contruir esse aqui em 2023.


**Proposta**

* Utilizar o iCloud e AirDrop.
* Desenvolver para iOS/MacOS.
* Usar as ferramentas da Adobe integradas ao sistema.

Hardware
---

**Razer Blade Stealth late 2019 GTX 1650**

| Item | Descrição |  &#124; 🗗 &#124; 🐧 |
| ---: | :--- | :--- |
| ``CPU`` | Quad-Core 10th Gen Intel® Core™ i7-1065G7 Processor with Hyper-Threading 1.3 GHz / 3.9 GHz (Base/Turbo) | ✅ &#124; ✅ &#124; ✅ |
| ``RAM`` | 16GB LPDDR4 3733MHz dual-channel | ✅ &#124; ✅ &#124; ✅ |
| ``iGPU`` | Intel UHD Iris Plus | ❌ &#124; ❌ &#124; ❌ |
| ``dGPU`` | NVIDIA® GeForce® GTX 1650 4GB GDDR5 VRAM | ❌ &#124; ❌ &#124; ❌ |
| ``SSD`` | 1TB Samsung 970 Evo Plus PCIe M.2 | ✅ &#124; ✅ &#124; ✅ |
| ``Monitor`` | 13.3" FHD Matte (1920 X 1080) 100% sRGB | ✅ &#124; ✅ &#124; ✅ |
| ``Webcam`` | Webcam (720P) | ✅ &#124; ✅ &#124; ✅ |
| ``WiFi`` | Dell Dw1560 BCM94352z | ✅ &#124; ✅ &#124; ✅ |
| ``USB`` | Type-A USB 3.1 | ✅ &#124; ✅ &#124; ✅ |
| ``Thunderbolt 3`` | USB-C 3.1 Gen 2 e Alimentação | ✅ &#124; ✅ &#124; ✅ |
| ``Som`` | Realtek ALC298 | ❌ &#124; ❌ &#124; ❌ |
| ``Bateria`` | 53Wh | ❌ &#124; ❌ &#124; ❌ |
| ``Teclado`` | Teclado Razer Chroma™ com ajuste de iluminação | ✅ &#124; ✅ &#124; ✅ |
| ``Touchpad`` | Precision Glass | ❌ &#124; ❌ &#124; ❌ |



Hardware Upgrades and Tools
---

Como o ``WiFI`` e o ``NVMe`` não são compatíveis com macOS foi necessário trocar. Troquei a placa de WiFi/Bluetooth por uma Broadcom (DW-1560) e o SSD original foi substituído por um Samsung 970 Evo Plus 1TB NVME M.2.


**Acessórios**

| Acessório | Descrição |
| ---: | :--- |
| ``USB mouse`` | O touchpad não funcionará e ainda não está funcionando |
| ``PenDrive 16GB+`` | Para criar o instalador | 

Diretórios
---
``EFI`` contem todos os arquivos necessários para carregar todos os sistemas operacionais.

``Files`` contem todos os arquivos que precisam ser compilados para criar DSDT exclusivas e resolver problemas.

``imgs`` é só um diretório para exibir imagens nesse readme.  

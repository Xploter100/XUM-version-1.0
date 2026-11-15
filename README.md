# XUM — sintetizador híbrido VST3

Plugin VST3 (JUCE 8 + C++17) para FL Studio en Windows x64.

## Compilar con GitHub
1. Sube esta carpeta a un repositorio (rama `main`).
2. Pestaña **Actions** → "Build XUM (VST3)" (se lanza solo con cada push).
3. Al terminar, descarga el artefacto **XUM-VST3-win64** y copia `XUM.vst3`
   a `C:\Program Files\Common Files\VST3\`.
4. En FL Studio: Options → Manage plugins → *Find installed plugins*.

## Arquitectura
```
Source/
  Parameters.h/.cpp        IDs, layout (APVTS), enums de fuentes/destinos de modulación
  PluginProcessor.*        MIDI sample-accurate, asignación/robo de voces, master, scope
  PluginEditor.*           GUI minimalista (osciloscopio + piano + controles básicos)
  Engine/Voice.h           Flujo: 3 osc + sub + ruido -> DualFilter -> ENV1 (amp)
  Engine/Oscillators.h     IOscEngine, unísono (16), WavetableBank/Engine, motores pendientes
  Engine/Filters.h         Ladder, SVF, Comb, Formantes; DualFilter serie/paralelo
  Engine/SubNoise.h        Sub-oscilador (4 ondas, octava, saturación) y ruido filtrado
  Modulation/Modulation.h  Envelope (tensión), Lfo (geométrico/caos), matriz de modulación
  UI/                      ScopeBuffer (lock-free) y componente Oscilloscope
```

## Estado
- Hecho: wavetable con interpolación entre frames + 2 warps, unísono 16, sub, ruido con
  envolvente, filtros duales, 10 LFOs (sync al DAW, S&H, caos logístico y Lorenz),
  4 ENV con tensión, 8 macros, matriz de 16 filas (fila 1 de ejemplo: ENV2 → F1 Cutoff).
- Pendiente (ya enrutados, solo falta `render()`): Multisample/SFZ, Sample, Granular, Spectral.
- Pendiente de UI: editor de la matriz, LFOs, selector de wavetables, presets.

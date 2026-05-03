const video = document.getElementById('videoPreview');
const fileInput = document.getElementById('fileInput');
const importBtn = document.getElementById('importBtn');
const exportBtn = document.getElementById('exportBtn');
const playBtn = document.getElementById('playBtn');
const timeline = document.getElementById('timeline');
const status = document.getElementById('status');
const timeDisplay = document.getElementById('timeDisplay');
const videoInfo = document.getElementById('videoInfo');
const trimStart = document.getElementById('trimStart');
const trimEnd = document.getElementById('trimEnd');
const volumeSlider = document.getElementById('volumeSlider');
const placeholderText = document.getElementById('placeholderText');

let currentClip = null;
let clips = [];

// Formato de tiempo
function formatTime(seconds) {
  const mins = Math.floor(seconds / 60);
  const secs = Math.floor(seconds % 60);
  return `${mins.toString().padStart(2, '0')}:${secs.toString().padStart(2, '0')}`;
}

// Importar video
importBtn.addEventListener('click', () => {
  fileInput.click();
});

fileInput.addEventListener('change', (e) => {
  const file = e.target.files[0];
  if (file) {
    const url = URL.createObjectURL(file);
    video.src = url;
    
    video.onloadedmetadata = () => {
      const duration = video.duration;
      
      currentClip = {
        id: Date.now(),
        name: file.name,
        path: url,
        duration: duration,
        trimStart: 0,
        trimEnd: duration,
        volume: 100
      };
      
      clips.push(currentClip);
      
      status.textContent = 'Video cargado';
      placeholderText.style.display = 'none';
      exportBtn.disabled = false;
      playBtn.disabled = false;
      
      trimStart.disabled = false;
      trimEnd.disabled = false;
      volumeSlider.disabled = false;
      
      trimEnd.value = duration.toFixed(2);
      videoInfo.textContent = `Duración: ${formatTime(duration)}`;
      
      updateTimeline();
    };
  }
});

// Actualizar timeline
function updateTimeline() {
  timeline.innerHTML = '';
  clips.forEach(clip => {
    const trackDiv = document.createElement('div');
    trackDiv.className = 'track';
    
    const clipDiv = document.createElement('div');
    clipDiv.className = 'clip';
    if (currentClip && currentClip.id === clip.id) {
      clipDiv.classList.add('selected');
    }
    
    const duration = clip.trimEnd - clip.trimStart;
    clipDiv.textContent = `${clip.name} (${formatTime(duration)})`;
    clipDiv.style.width = Math.max(duration * 20, 100) + 'px';
    
    clipDiv.addEventListener('click', () => {
      currentClip = clip;
      updateTimeline();
      video.src = clip.path;
      trimStart.value = clip.trimStart.toFixed(2);
      trimEnd.value = clip.trimEnd.toFixed(2);
      volumeSlider.value = clip.volume;
    });
    
    trackDiv.appendChild(clipDiv);
    timeline.appendChild(trackDiv);
  });
}

// Actualizar propiedades
trimStart.addEventListener('change', (e) => {
  if (currentClip) {
    currentClip.trimStart = parseFloat(e.target.value);
    updateTimeline();
  }
});

trimEnd.addEventListener('change', (e) => {
  if (currentClip) {
    currentClip.trimEnd = parseFloat(e.target.value);
    updateTimeline();
  }
});

volumeSlider.addEventListener('input', (e) => {
  const volume = parseFloat(e.target.value) / 100;
  video.volume = volume;
  if (currentClip) {
    currentClip.volume = parseFloat(e.target.value);
  }
});

// Reproducción
playBtn.addEventListener('click', () => {
  if (video.paused) {
    video.play();
    playBtn.textContent = '⏸ Pausa';
  } else {
    video.pause();
    playBtn.textContent = '▶ Reproducir';
  }
});

// Actualizar tiempo
video.addEventListener('timeupdate', () => {
  timeDisplay.textContent = `${formatTime(video.currentTime)} / ${formatTime(video.duration)}`;
});

// Exportar video
exportBtn.addEventListener('click', async () => {
  if (clips.length === 0) {
    alert('No hay videos para exportar');
    return;
  }
  
  status.textContent = 'Preparando exportación...';
  
  const config = {
    clips: clips.map(c => ({
      path: c.path,
      trimStart: c.trimStart,
      trimEnd: c.trimEnd,
      volume: c.volume
    })),
    output: 'output.mp4'
  };
  
  try {
    const result = await window.electronAPI.exportVideo(config);
    if (result.success) {
      status.textContent = '✓ Video exportado como output.mp4';
      alert('Video exportado exitosamente: output.mp4');
    }
  } catch (err) {
    status.textContent = '✗ Error en exportación';
    console.error(err);
  }
});

console.log('Video editor MVP cargado');

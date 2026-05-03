import { contextBridge, ipcRenderer } from 'electron';

contextBridge.exposeInMainWorld('electronAPI', {
  importVideo: (filePath) => ipcRenderer.invoke('import-video', filePath),
  exportVideo: (config) => ipcRenderer.invoke('export-video', config),
  onVideoLoaded: (callback) => ipcRenderer.on('video-loaded', callback)
});

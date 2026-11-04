#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

#define RECORDFILE "recorded_sound.raw"
#define SAMPLE_RATE 44100
#define CHANNELS 2
#define DURATION_SECONDS 30

static int configure_capture(snd_pcm_t *capture_handle, unsigned int *rate)
{
    snd_pcm_hw_params_t *hw_params;
    int err;

    snd_pcm_hw_params_alloca(&hw_params);

    if ((err = snd_pcm_hw_params_any(capture_handle, hw_params)) < 0) {
        fprintf(stderr, "Error: Cannot initialize hardware parameter structure (%s)\n", snd_strerror(err));
        return err;
    }

    if ((err = snd_pcm_hw_params_set_access(capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
        fprintf(stderr, "Error: Cannot set access type (%s)\n", snd_strerror(err));
        return err;
    }

    if ((err = snd_pcm_hw_params_set_format(capture_handle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0) {
        fprintf(stderr, "Error: Cannot set sample format (%s)\n", snd_strerror(err));
        return err;
    }

    if ((err = snd_pcm_hw_params_set_rate_near(capture_handle, hw_params, rate, 0)) < 0) {
        fprintf(stderr, "Error: Cannot set sample rate (%s)\n", snd_strerror(err));
        return err;
    }

    if ((err = snd_pcm_hw_params_set_channels(capture_handle, hw_params, CHANNELS)) < 0) {
        fprintf(stderr, "Error: Cannot set channel count (%s)\n", snd_strerror(err));
        return err;
    }

    if ((err = snd_pcm_hw_params(capture_handle, hw_params)) < 0) {
        fprintf(stderr, "Error: Cannot apply hardware parameters (%s)\n", snd_strerror(err));
        return err;
    }

    if ((err = snd_pcm_prepare(capture_handle)) < 0) {
        fprintf(stderr, "Error: Cannot prepare audio interface for use (%s)\n", snd_strerror(err));
        return err;
    }

    return 0;
}

static int record_audio(snd_pcm_t *capture_handle, FILE *fp, snd_pcm_uframes_t frames)
{
    const size_t buffer_size = frames * CHANNELS * 2;
    char *buffer = malloc(buffer_size);
    int status = 0;

    if (!buffer) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return -1;
    }

    long loops = (SAMPLE_RATE * DURATION_SECONDS) / frames;
    printf("Recording for %d seconds...\n", DURATION_SECONDS);

    for (long i = 0; i < loops; i++) {
        int err = snd_pcm_readi(capture_handle, buffer, frames);

        if (err == -EPIPE) {
            fprintf(stderr, "Warning: Overrun occurred! Resuming...\n");
            err = snd_pcm_prepare(capture_handle);
            if (err < 0) {
                fprintf(stderr, "Error: Cannot resume audio interface (%s)\n", snd_strerror(err));
                status = -1;
                break;
            }
        } else if (err < 0) {
            fprintf(stderr, "Error: Failed reading data from device (%s)\n", snd_strerror(err));
            status = -1;
            break;
        } else if (err != (int)frames) {
            fprintf(stderr, "Warning: Short read, read %d frames\n", err);
        }

        if (fwrite(buffer, 1, buffer_size, fp) != buffer_size) {
            fprintf(stderr, "Error: Failed writing audio data to output file.\n");
            status = -1;
            break;
        }
    }

    free(buffer);
    return status;
}

int main(void)
{
    printf("hello I am audio_app ! \n");

    unsigned int rate = SAMPLE_RATE;
    snd_pcm_t *capture_handle;
    snd_pcm_uframes_t frames = 128;
    FILE *fp = fopen(RECORDFILE, "wb");
    if (!fp) {
        fprintf(stderr, "Error: Cannot open output audio file.\n");
        return 1;
    }

    int err = snd_pcm_open(&capture_handle, "default", SND_PCM_STREAM_CAPTURE, 0);
    if (err < 0) {
        fprintf(stderr, "Error: Cannot open audio device (%s)\n", snd_strerror(err));
        fclose(fp);
        return 1;
    }

    int status = 1;
    if (configure_capture(capture_handle, &rate) == 0 &&
        record_audio(capture_handle, fp, frames) == 0) {
        printf("Recording complete! Audio data saved to '%s'.\n", RECORDFILE);
        status = 0;
    }

    snd_pcm_close(capture_handle);
    fclose(fp);
    return status;
}

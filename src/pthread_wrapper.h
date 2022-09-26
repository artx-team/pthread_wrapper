#pragma once

/* Single header `pthread` wrapper which aborts execution on errors.
 */

#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>

#ifndef __pthread_has_builtin
#   ifdef __has_builtin
#       define __pthread_has_builtin(x) __has_builtin(x)
#   else
#       define __pthread_has_builtin(x) (0)
#   endif
#endif

#ifndef __pthread_unlikely
#   if defined(__GNUC__) || __pthread_has_builtin(__builtin_expect)
#       define __pthread_unlikely(x) (__builtin_expect(!!(x), 0))
#   else
#       define __pthread_unlikely(x) (x)
#   endif
#endif

#define __pthread_concat(x, y) __pthread_concat_helper(x, y)
#define __pthread_concat_helper(x, y) x ## y

#define __pthread_var(...) __pthread_var_helper(__VA_ARGS__, 2, 1)
#define __pthread_var_helper(v, x, y, ...) __pthread_var ## y (v, x)
#define __pthread_var1(x, y) __pthread_var2(x, __pthread_concat(y, __LINE__))
#define __pthread_var2(x, y) __pthread_concat(__pthread_tmp, __pthread_concat(y, x))

#define __pthread_rc(__pthread_func, __rc, ...) __extension__ ({ \
        int __pthread_var(rc) = (__pthread_func)(__VA_ARGS__); \
        if (__pthread_unlikely(__pthread_var(rc) && __pthread_var(rc) != (__rc))) \
            abort(); \
        __pthread_var(rc); \
    })

// common
#define pthread_once(...)                       __pthread_rc(pthread_once, 0, ## __VA_ARGS__)
#define pthread_kill(...)                       __pthread_rc(pthread_kill, 0, ## __VA_ARGS__)
#define pthread_yield(...)                      __pthread_rc(pthread_yield, 0, ## __VA_ARGS__)
#define pthread_sigmask(...)                    __pthread_rc(pthread_sigmask, 0, ## __VA_ARGS__)
#define pthread_sigqueue(...)                   __pthread_rc(pthread_sigqueue, 0, ## __VA_ARGS__)
#define pthread_getconcurrency(...)             __pthread_rc(pthread_getconcurrency, 0, ## __VA_ARGS__)
#define pthread_setconcurrency(...)             __pthread_rc(pthread_setconcurrency, 0, ## __VA_ARGS__)
#define pthread_setcancelstate(...)             __pthread_rc(pthread_setcancelstate, 0, ## __VA_ARGS__)
#define pthread_setcanceltype(...)              __pthread_rc(pthread_setcanceltype, 0, ## __VA_ARGS__)
#define pthread_atfork(...)                     __pthread_rc(pthread_atfork, 0, ## __VA_ARGS__)

// pthread_key_t
#define pthread_key_create(...)                 __pthread_rc(pthread_key_create, 0, ## __VA_ARGS__)
#define pthread_key_delete(...)                 __pthread_rc(pthread_key_delete, 0, ## __VA_ARGS__)
#define pthread_setspecific(...)                __pthread_rc(pthread_setspecific, 0, ## __VA_ARGS__)

// pthread_attr_t
#define pthread_attr_init(...)                  __pthread_rc(pthread_attr_init, 0, ## __VA_ARGS__)
#define pthread_attr_destroy(...)               __pthread_rc(pthread_attr_destroy, 0, ## __VA_ARGS__)
#define pthread_attr_getdetachstate(...)        __pthread_rc(pthread_attr_getdetachstate, 0, ## __VA_ARGS__)
#define pthread_attr_setdetachstate(...)        __pthread_rc(pthread_attr_setdetachstate, 0, ## __VA_ARGS__)
#define pthread_attr_getguardsize(...)          __pthread_rc(pthread_attr_getguardsize, 0, ## __VA_ARGS__)
#define pthread_attr_setguardsize(...)          __pthread_rc(pthread_attr_setguardsize, 0, ## __VA_ARGS__)
#define pthread_attr_getschedparam(...)         __pthread_rc(pthread_attr_getschedparam, 0, ## __VA_ARGS__)
#define pthread_attr_setschedparam(...)         __pthread_rc(pthread_attr_setschedparam, 0, ## __VA_ARGS__)
#define pthread_attr_getschedpolicy(...)        __pthread_rc(pthread_attr_getschedpolicy, 0, ## __VA_ARGS__)
#define pthread_attr_setschedpolicy(...)        __pthread_rc(pthread_attr_setschedpolicy, 0, ## __VA_ARGS__)
#define pthread_attr_getinheritsched(...)       __pthread_rc(pthread_attr_getinheritsched, 0, ## __VA_ARGS__)
#define pthread_attr_setinheritsched(...)       __pthread_rc(pthread_attr_setinheritsched, 0, ## __VA_ARGS__)
#define pthread_attr_getscope(...)              __pthread_rc(pthread_attr_getscope, 0, ## __VA_ARGS__)
#define pthread_attr_setscope(...)              __pthread_rc(pthread_attr_setscope, 0, ## __VA_ARGS__)
#define pthread_attr_getstackaddr(...)          __pthread_rc(pthread_attr_getstackaddr, 0, ## __VA_ARGS__)
#define pthread_attr_setstackaddr(...)          __pthread_rc(pthread_attr_setstackaddr, 0, ## __VA_ARGS__)
#define pthread_attr_getstacksize(...)          __pthread_rc(pthread_attr_getstacksize, 0, ## __VA_ARGS__)
#define pthread_attr_setstacksize(...)          __pthread_rc(pthread_attr_setstacksize, 0, ## __VA_ARGS__)
#define pthread_attr_getstack(...)              __pthread_rc(pthread_attr_getstack, 0, ## __VA_ARGS__)
#define pthread_attr_setstack(...)              __pthread_rc(pthread_attr_setstack, 0, ## __VA_ARGS__)
#define pthread_attr_getaffinity_np(...)        __pthread_rc(pthread_attr_getaffinity_np, 0, ## __VA_ARGS__)
#define pthread_attr_setaffinity_np(...)        __pthread_rc(pthread_attr_setaffinity_np, 0, ## __VA_ARGS__)
#define pthread_attr_getsigmask_np(...)         __pthread_rc(pthread_attr_getsigmask_np, PTHREAD_ATTR_NO_SIGMASK_NP, ## __VA_ARGS__)
#define pthread_attr_setsigmask_np(...)         __pthread_rc(pthread_attr_setsigmask_np, 0, ## __VA_ARGS__)
#define pthread_getattr_default_np(...)         __pthread_rc(pthread_getattr_default_np, 0, ## __VA_ARGS__)
#define pthread_setattr_default_np(...)         __pthread_rc(pthread_setattr_default_np, 0, ## __VA_ARGS__)
#define pthread_getattr_np(...)                 __pthread_rc(pthread_getattr_np, 0, ## __VA_ARGS__)

// pthread_t
#define pthread_create(...)                     __pthread_rc(pthread_create, 0, ## __VA_ARGS__)
#define pthread_join(...)                       __pthread_rc(pthread_join, 0, ## __VA_ARGS__)
#define pthread_tryjoin_np(...)                 __pthread_rc(pthread_tryjoin_np, EBUSY, ## __VA_ARGS__)
#define pthread_timedjoin_np(...)               __pthread_rc(pthread_tryjoin_np, ETIMEDOUT, ## __VA_ARGS__)
#define pthread_clockjoin_np(...)               __pthread_rc(pthread_clockjoin_np, ETIMEDOUT, ## __VA_ARGS__)
#define pthread_detach(...)                     __pthread_rc(pthread_detach, 0, ## __VA_ARGS__)
#define pthread_cancel(...)                     __pthread_rc(pthread_cancel, 0, ## __VA_ARGS__)
#define pthread_setschedparam(...)              __pthread_rc(pthread_setschedparam, 0, ## __VA_ARGS__)
#define pthread_getschedparam(...)              __pthread_rc(pthread_getschedparam, 0, ## __VA_ARGS__)
#define pthread_setschedprio(...)               __pthread_rc(pthread_setschedprio, 0, ## __VA_ARGS__)
#define pthread_getname_np(...)                 __pthread_rc(pthread_getname_np, ERANGE, ## __VA_ARGS__)
#define pthread_setname_np(...)                 __pthread_rc(pthread_setname_np, ERANGE, ## __VA_ARGS__)
#define pthread_getaffinity_np(...)             __pthread_rc(pthread_getaffinity_np, 0, ## __VA_ARGS__)
#define pthread_setaffinity_np(...)             __pthread_rc(pthread_setaffinity_np, 0, ## __VA_ARGS__)
#define pthread_getcpuclockid(...)              __pthread_rc(pthread_getcpuclockid, 0, ## __VA_ARGS__)

// pthread_mutexattr_t
#define pthread_mutexattr_init(...)             __pthread_rc(pthread_mutexattr_init, 0, ## __VA_ARGS__)
#define pthread_mutexattr_destroy(...)          __pthread_rc(pthread_mutexattr_destroy, 0, ## __VA_ARGS__)
#define pthread_mutexattr_getpshared(...)       __pthread_rc(pthread_mutexattr_getpshared, 0, ## __VA_ARGS__)
#define pthread_mutexattr_setpshared(...)       __pthread_rc(pthread_mutexattr_setpshared, 0, ## __VA_ARGS__)
#define pthread_mutexattr_gettype(...)          __pthread_rc(pthread_mutexattr_gettype, 0, ## __VA_ARGS__)
#define pthread_mutexattr_settype(...)          __pthread_rc(pthread_mutexattr_settype, 0, ## __VA_ARGS__)
#define pthread_mutexattr_getprotocol(...)      __pthread_rc(pthread_mutexattr_getprotocol, 0, ## __VA_ARGS__)
#define pthread_mutexattr_setprotocol(...)      __pthread_rc(pthread_mutexattr_setprotocol, 0, ## __VA_ARGS__)
#define pthread_mutexattr_getprioceiling(...)   __pthread_rc(pthread_mutexattr_getprioceiling, 0, ## __VA_ARGS__)
#define pthread_mutexattr_setprioceiling(...)   __pthread_rc(pthread_mutexattr_setprioceiling, 0, ## __VA_ARGS__)
#define pthread_mutexattr_getrobust(...)        __pthread_rc(pthread_mutexattr_getrobust, 0, ## __VA_ARGS__)
#define pthread_mutexattr_setrobust(...)        __pthread_rc(pthread_mutexattr_setrobust, 0, ## __VA_ARGS__)
#define pthread_mutexattr_getrobust_np(...)     __pthread_rc(pthread_mutexattr_getrobust_np, 0, ## __VA_ARGS__)
#define pthread_mutexattr_setrobust_np(...)     __pthread_rc(pthread_mutexattr_setrobust_np, 0, ## __VA_ARGS__)

// pthread_mutex_t
#ifndef NDEBUG
#define pthread_mutex_init(lock, attr) __extension__ ({ \
        int __pthread_var(rc); \
        pthread_mutexattr_t *__pthread_var(tmp) = (attr); \
        if (!__pthread_var(tmp)) { \
            pthread_mutexattr_t __pthread_var(err); \
            pthread_mutexattr_init(&__pthread_var(err)); \
            pthread_mutexattr_settype(&__pthread_var(err), PTHREAD_MUTEX_ERRORCHECK); \
            __pthread_var(rc) = __pthread_rc(pthread_mutex_init, 0, lock, &__pthread_var(err)); \
            pthread_mutexattr_destroy(&__pthread_var(err)); \
        } else { \
            __pthread_var(rc) = __pthread_rc(pthread_mutex_init, 0, lock, __pthread_var(tmp)); \
        } \
        __pthread_var(rc); \
    })
#else
#define pthread_mutex_init(...)                 __pthread_rc(pthread_mutex_init, 0, ## __VA_ARGS__)
#endif
#define pthread_mutex_destroy(...)              __pthread_rc(pthread_mutex_destroy, 0, ## __VA_ARGS__)
#define pthread_mutex_lock(...)                 __pthread_rc(pthread_mutex_lock, 0, ## __VA_ARGS__)
#define pthread_mutex_trylock(...)              __pthread_rc(pthread_mutex_trylock, EBUSY, ## __VA_ARGS__)
#define pthread_mutex_timedlock(...)            __pthread_rc(pthread_mutex_timedlock, ETIMEDOUT, ## __VA_ARGS__)
#define pthread_mutex_clocklock(...)            __pthread_rc(pthread_mutex_clocklock, ETIMEDOUT, ## __VA_ARGS__)
#define pthread_mutex_unlock(...)               __pthread_rc(pthread_mutex_unlock, 0, ## __VA_ARGS__)
#define pthread_mutex_getprioceiling(...)       __pthread_rc(pthread_mutex_getprioceiling, 0, ## __VA_ARGS__)
#define pthread_mutex_setprioceiling(...)       __pthread_rc(pthread_mutex_setprioceiling, 0, ## __VA_ARGS__)
#define pthread_mutex_consistent(...)           __pthread_rc(pthread_mutex_consistent, 0, ## __VA_ARGS__)
#define pthread_mutex_consistent_np(...)        __pthread_rc(pthread_mutex_consistent_np, 0, ## __VA_ARGS__)

// pthread_rwlockattr_t
#define pthread_rwlockattr_init(...)            __pthread_rc(pthread_rwlockattr_init, 0, ## __VA_ARGS__)
#define pthread_rwlockattr_destroy(...)         __pthread_rc(pthread_rwlockattr_destroy, 0, ## __VA_ARGS__)
#define pthread_rwlockattr_getpshared(...)      __pthread_rc(pthread_rwlockattr_getpshared, 0, ## __VA_ARGS__)
#define pthread_rwlockattr_setpshared(...)      __pthread_rc(pthread_rwlockattr_setpshared, 0, ## __VA_ARGS__)
#define pthread_rwlockattr_getkind_np(...)      __pthread_rc(pthread_rwlockattr_getkind_np, 0, ## __VA_ARGS__)
#define pthread_rwlockattr_setkind_np(...)      __pthread_rc(pthread_rwlockattr_setkind_np, 0, ## __VA_ARGS__)

// pthread_rwlock_t
#define pthread_rwlock_init(...)                __pthread_rc(pthread_rwlock_init, 0, ## __VA_ARGS__)
#define pthread_rwlock_destroy(...)             __pthread_rc(pthread_rwlock_destroy, 0, ## __VA_ARGS__)
#define pthread_rwlock_rdlock(...)              __pthread_rc(pthread_rwlock_rdlock, 0, ## __VA_ARGS__)
#define pthread_rwlock_tryrdlock(...)           __pthread_rc(pthread_rwlock_tryrdlock, EBUSY, ## __VA_ARGS__)
#define pthread_rwlock_timedrdlock(...)         __pthread_rc(pthread_rwlock_timedrdlock, ETIMEDOUT, ## __VA_ARGS__)
#define pthread_rwlock_clockrdlock(...)         __pthread_rc(pthread_rwlock_clockrdlock, ETIMEDOUT, ## __VA_ARGS__)
#define pthread_rwlock_wrlock(...)              __pthread_rc(pthread_rwlock_wrlock, 0, ## __VA_ARGS__)
#define pthread_rwlock_trywrlock(...)           __pthread_rc(pthread_rwlock_trywrlock, EBUSY, ## __VA_ARGS__)
#define pthread_rwlock_timedwrlock(...)         __pthread_rc(pthread_rwlock_timedwrlock, ETIMEDOUT, ## __VA_ARGS__)
#define pthread_rwlock_clockwrlock(...)         __pthread_rc(pthread_rwlock_clockwrlock, ETIMEDOUT, ## __VA_ARGS__)
#define pthread_rwlock_unlock(...)              __pthread_rc(pthread_rwlock_unlock, 0, ## __VA_ARGS__)

// pthread_condattr_t
#define pthread_condattr_init(...)              __pthread_rc(pthread_condattr_init, 0, ## __VA_ARGS__)
#define pthread_condattr_destroy(...)           __pthread_rc(pthread_condattr_destroy, 0, ## __VA_ARGS__)
#define pthread_condattr_getpshared(...)        __pthread_rc(pthread_condattr_getpshared, 0, ## __VA_ARGS__)
#define pthread_condattr_setpshared(...)        __pthread_rc(pthread_condattr_setpshared, 0, ## __VA_ARGS__)
#define pthread_condattr_getclock(...)          __pthread_rc(pthread_condattr_getclock, 0, ## __VA_ARGS__)
#define pthread_condattr_setclock(...)          __pthread_rc(pthread_condattr_setclock, 0, ## __VA_ARGS__)

// pthread_cond_t
#define pthread_cond_init(...)                  __pthread_rc(pthread_cond_init, 0, ## __VA_ARGS__)
#define pthread_cond_destroy(...)               __pthread_rc(pthread_cond_destroy, 0, ## __VA_ARGS__)
#define pthread_cond_signal(...)                __pthread_rc(pthread_cond_signal, 0, ## __VA_ARGS__)
#define pthread_cond_broadcast(...)             __pthread_rc(pthread_cond_broadcast, 0, ## __VA_ARGS__)
#define pthread_cond_wait(...)                  __pthread_rc(pthread_cond_wait, 0, ## __VA_ARGS__)
#define pthread_cond_timedwait(...)             __pthread_rc(pthread_cond_timedwait, ETIMEDOUT, ## __VA_ARGS__)
#define pthread_cond_clockwait(...)             __pthread_rc(pthread_cond_clockwait, ETIMEDOUT, ## __VA_ARGS__)

// pthread_spinlock_t
#define pthread_spin_init(...)                  __pthread_rc(pthread_spin_init, 0, ## __VA_ARGS__)
#define pthread_spin_destroy(...)               __pthread_rc(pthread_spin_destroy, 0, ## __VA_ARGS__)
#define pthread_spin_lock(...)                  __pthread_rc(pthread_spin_lock, 0, ## __VA_ARGS__)
#define pthread_spin_trylock(...)               __pthread_rc(pthread_spin_trylock, EBUSY, ## __VA_ARGS__)
#define pthread_spin_unlock(...)                __pthread_rc(pthread_spin_unlock, 0, ## __VA_ARGS__)

// pthread_barrierattr_t
#define pthread_barrierattr_init(...)           __pthread_rc(pthread_barrierattr_init, 0, ## __VA_ARGS__)
#define pthread_barrierattr_destroy(...)        __pthread_rc(pthread_barrierattr_destroy, 0, ## __VA_ARGS__)
#define pthread_barrierattr_getpshared(...)     __pthread_rc(pthread_barrierattr_getpshared, 0, ## __VA_ARGS__)
#define pthread_barrierattr_setpshared(...)     __pthread_rc(pthread_barrierattr_setpshared, 0, ## __VA_ARGS__)

// pthread_barrier_t
#define pthread_barrier_init(...)               __pthread_rc(pthread_barrier_init, 0, ## __VA_ARGS__)
#define pthread_barrier_destroy(...)            __pthread_rc(pthread_barrier_destroy, 0, ## __VA_ARGS__)
#define pthread_barrier_wait(...)               __pthread_rc(pthread_barrier_wait, PTHREAD_BARRIER_SERIAL_THREAD, ## __VA_ARGS__)

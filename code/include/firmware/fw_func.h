#ifndef FW_FUNC_H
#define FW_FUNC

/**
 * @brief default trap handler for m-mode
 * 
 */
void _m_trap_handler(void);

/**
 * @brief enables pmp in m-mode using pmpcfg0
 * 
 */
void enable_pmp(void);

/**
 * @brief switches to S mode
 * 
 */
void switch_priv_M_to_S(void);

#endif /* FW_FUNC_H */